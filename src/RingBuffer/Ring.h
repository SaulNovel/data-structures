#ifndef RING_BUFFER
#define RING_BUFFER

#include <iostream>
#include <string>
#include <algorithm>

namespace Containers
{

template<class T>
class ring 
{

private:
    size_t m_size;
    size_t m_pos;
    T* m_values;

private:
    void swap(ring& other) {
        std::swap(this->m_size, other.m_size);
        std::swap(this->m_pos, other.m_pos);
        std::swap(this->m_values, other.m_values);
    }

public:
    class iterator;

public:
    ring(size_t size) : m_size(size), m_pos(0), m_values(nullptr) {
        m_values = new T[size];
    }

    ring(const ring& other) {
        T* temp = new T[other.m_size];
        std::copy(other.m_values, other.m_values+other.m_size, this->m_values);
        
        delete[] this->m_values;
        this->m_values = temp;
        this->m_pos = other.m_pos;
    }

    ring& operator=(const ring& other) {
        ring temp(other);
        swap(temp);

        return *this;
    }

    ring(ring&& other) {
        swap(other);
    }

    ring& operator=(ring&& other) {
        if (this == &other) {
            return *this;
        }
        swap(other);
        other.m_values = nullptr;

        return *this;
    }

    ~ring() {
        delete[] m_values;
    }

    size_t size() const {
        return m_size;
    }

    void add(const T& value) {
        m_values[m_pos++] = value;
        m_pos = (m_pos >= m_size) ? 0 : m_pos;
    }

    T& get(size_t index) {
        if (index >= m_size ) {
            throw std::out_of_range("index " + std::to_string(index) + " is out of range");
        }
        return m_values[index];
    }

    iterator begin() {
        return iterator(0, *this);
    }

    iterator end() {
        return iterator(m_size, *this);
    }

};

// Nested class (implemented outside)
template<class T>
class ring<T>::iterator {

private:
    size_t m_pos;
    ring& m_ring;

public:

    iterator(size_t pos, ring& obj) : m_pos(pos), m_ring(obj) { }

    iterator(const iterator& other) : m_ring(other.m_ring) {
        this->m_pos = other.m_pos;
    }

    /**
     * Overloading Postfix ++operator
     * - Performs the increment and returns the original value
     * - To do this it must have a copy of the original value
     * - The postfix operator takes a dummy argument, to give it a different signature from the prefix operator
    */
    iterator& operator++(int) {
        m_pos++;
        
        return *this;
    }

    /**
     * Overloading Prefix ++operator
     * - The prefix operator performs the increment and returns the incremented value
    */
    iterator& operator++() {
        m_pos++;

        return *this;
    }

    iterator& operator--(int) {
        m_pos--;
        
        return *this;
    }

    iterator& operator--() {
        m_pos--;

        return *this;
    }

    T& operator*() const {
        return m_ring.get(m_pos);
    }

    bool operator==(const iterator& other) const {
        return m_pos == other.m_pos;
    }

    bool operator!=(const iterator& other) const {
        return !operator==(other);
    }
};

}

#endif