#ifndef CUSTOM_VECTOR
#define CUSTOM_VECTOR

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <memory.h>

/* Imitates a std::vector constainer
The C++ standard specifies that a legal (i.e., standard-conforming) 
implementation of vector must satisfy the following performance requirements:

    Operation	    Speed
    vector()	    O(1)
    vector(n, x)	O(n)
    size()	        O(1)
    v[i]	        O(1)
    push_back(x)	O(1)
    pop_back	    O(1)
    insert	        O(size())
    erase	        O(size())
    front, back	    O(1)

Rule of 5:
 - Destructor
 - Copy constructor
 - Copy assignment operator
 - Move constructor
 - Move assignement operator

*/

template<typename Vector>
class VectorIterator
{
public:
    using pointer           = typename Vector::pointer;
    using const_pointer     = typename Vector::const_pointer;
    using reference         = typename Vector::reference;
    using const_reference   = typename Vector::const_reference;

public:
    VectorIterator(pointer ptr)
    : m_Ptr(ptr) {}

    VectorIterator& operator++()
    {
        m_Ptr++;
        return *this;
    }

    VectorIterator operator++(int32_t)
    {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    VectorIterator& operator--()
    {
        m_Ptr--;
        return *this;
    }

    VectorIterator operator--(int32_t)
    {
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }

    reference operator[](int32_t index)
    {
        return *(m_Ptr + index);
    }

    pointer operator->()
    {
        return m_Ptr;
    }

    reference operator*()
    {
        return *m_Ptr;
    }

    const_pointer operator->() const
    {
        return m_Ptr;
    }

    const_reference operator*() const
    {
        std::cout << "const reference " << std::endl;
        return *m_Ptr;
    }

    bool operator==(const VectorIterator& other) const
    {
        return m_Ptr == other.m_Ptr;
    }

    bool operator!=(const VectorIterator& other) const
    {
        return !(*this == other);
    }

private:
    pointer m_Ptr;
};

template<typename T>
class Vector {

public:

    /*---- Member types -----------------------------------------*/

    using value_type        = T;
    using reference         = T&;
    using const_reference   = T const&;
    using pointer           = T*;
    using const_pointer     = const T*;

    using iterator          = VectorIterator<Vector<T>>;
    using const_iterator    = VectorIterator<Vector<const T>>;
    using size_type         = std::size_t;

    //iterator begin() { return iterator(m_Data); }
    //const_iterator cbegin() const { std::cout << "const begin" << std::endl; return const_iterator(m_Data); }

public:

    /**
    * Constructor
    * Allocates space but does not call the constructor
    * Useful if the type T has an expensive constructor
    * We preallocate space without initializing it giving 
    * room to grow and shrink the buffer without re-allocating.
    * 
    * @param start 
    * @param end
    */
    Vector(const size_type& capacity = 0, const T& value = T())
    : m_Capacity(capacity)
    , m_Size(capacity)
    , m_Data(static_cast<T*>(::operator new(capacity * sizeof(T))))
    { 
        if (capacity == 0) { return; }

        fill_m_Data(0, capacity, value);
    }

    /**
    * Destructor
    * Because elements are constructed in-place using placement new.
    * Then we must manually call the destructor on the elements.
    */
    ~Vector()
    {
        clear();
        ::operator delete(m_Data);
    }

    /**
    * Copy constructor
    * Elements are constructed in-place using placement new.
    */
    Vector(const Vector& v)
    : m_Capacity(v.m_Capacity)
    , m_Size(v.m_Size)
    , m_Data(static_cast<T*>(::operator new(v.m_Capacity * sizeof(T))))
    {
        for (size_t i = 0; i < v.m_Size; i++) {
            // placement operator
            new(&m_Data[i]) T(v.at(i));
        }    
    }

    // Copy assignement operator
    Vector& operator=(const Vector& v)
    {
        if (&v == this) {
            return *this;
        }

        Vector tmp(v);
        tmp.swap(*this);
        return *this;
    }

    /**
    * Move constructor
    * The parameter passed is the source object and the state used to define the new object's state
    * The source object is left in a valid (but can be undefined state, 
    * for example no longer the owner of the internal buffer anymore).
    * 
    * @param v 
    */
    Vector(Vector &&v)
    : m_Capacity(0)
    , m_Size(0)
    , m_Data(nullptr)
    {        
        v.swap(*this);
    }

    /**
    * Move assignement operator
    * The parameter passed is the source object and the state used to define the new object's state
    * The source object is left in a valid (but can be undefined state, 
    * for example no longer the owner of the internal buffer anymore).
    * 
    * @param v 
    */
    Vector& operator=(Vector &&v)
    {
        if (this == &v) {
            return *this;
        }
        
        v.swap(*this);
        return *this;
    }

    /*---- Capacity ---------------------------------------------*/

    size_type size() const { return m_Size; }

    size_type capacity() const { return m_Capacity; }
    
    bool empty() { return m_Size == 0; }

    /**
    * Increase the capacity of the vector to a value that's greater than capacity().
    * If capacity is greater than the current capacity(), new storage is allocated,
    * otherwise the method does nothing.
    * 
    * @param capacity
    */
    void reserve(const size_type& capacity)
    {
        if (capacity <= m_Capacity) { return; }

        reAlloc(capacity);
    }

    // copy previous elements
    // add more elements at the end
    void resize(const size_type& size, const T& value = T())
    {
        T* newBlock = (T*)::operator new(size * sizeof(T));

        size_type length = (size > m_Size) ? m_Size : size;

        for (size_t i = 0; i < length; i++) {
            // placement operator
            new(&newBlock[i]) T(m_Data[i]);
        }

        clear();
        ::operator delete(m_Data);

        m_Data = newBlock;
        m_Capacity = size;
        m_Size = size;

        if (size <= length) { return; }

        // initialize rest of the elements
        fill_m_Data(length, size, value);
    }

    /*---- Element access ---------------------------------------*/

    T* data() { return m_Data; }

    // Non-Validated element access
    T& operator[](size_type index) { return m_Data[index]; }

    const T& operator[](size_type index) const { return m_Data[index]; }

    // Validated element access
    T& at(size_type index)
    {
        if (index < 0 || index >= m_Size)
        {
            throw std::out_of_range("index " + std::to_string(index) + " is out of range");
        }
        return m_Data[index];
    }

    const T& at(size_type index) const
    {
        if (index < 0 || index >= m_Size)
        {
            throw std::out_of_range("index " + std::to_string(index) + " is out of range");
        }
        return m_Data[index];
    }

    /*---- Modifiers --------------------------------------------*/

    /**
    * Adds an element to the end, increases size()
    * Increases capacity() if needed
    * 
    * @param value
    * 
    */
    void push_back(const T& value)
    {
        reaAlloc_if_required();
        
        new(&m_Data[m_Size++]) T(value);
    }

    void push_back(T&& value)
    {
        reaAlloc_if_required();

        new(&m_Data[m_Size++]) T(std::move(value));
    }

    /**
    * Constructs an element in-place at the end, increases size()
    * Increases capacity() if needed
    * 
    * @param args
    * 
    */
    template<typename... Args>
    T& emplace_back(Args&& ... args)
    {
        reaAlloc_if_required();

        // Construct the element in place: placement new
        new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
        // m_Data[m_size] = T(std::forward<Args>(args)...);
       
        return m_Data[m_Size++];
    }

    /**
    * Removes the last element, decreases size()
    * Does not modify capacity(), calls to the element destructor
    * 
    */
    void pop_back()
    {
        if (m_Size > 0) { m_Data[--m_Size].~T(); }
    }


    /**
    * Erases all elements from the container.
    * After this call, size() returns zero.
    * 
    */
    void clear()
    {
        for (size_t i = 0; i < m_Size; i++) {
            m_Data[i].~T();
        }
        m_Size = 0;
    }

    void swap(Vector &v)
    {
        using std::swap;
        swap(m_Capacity, v.m_Capacity);
        swap(m_Size, v.m_Size);
        swap(m_Data, v.m_Data);
    }

    /*---- Iterators --------------------------------------------*/

    iterator begin() { return iterator(m_Data); }
    const_iterator cbegin() const { return const_iterator(m_Data); }

    iterator end() { return iterator(m_Data + m_Size); }
    const_iterator cend() const { return const_iterator(m_Data + m_Size); }


private:
    // Size of the array
    size_type m_Capacity = 0;
    // Number of elements in the array
    size_type m_Size = 0;

    T* m_Data = nullptr;

    void reaAlloc_if_required()
    {
        if (m_Size >= m_Capacity) {
            size_type newCapacity = (m_Capacity == 0) ? 1 : (m_Capacity * 2);
            reAlloc(newCapacity);
        }
    }

    /**
    * Allocates a new block of memory
    * Copies/moves old elements into new blocks
    * Deletes old block
    *
    * @param start 
    * @param end
    */
    void reAlloc(size_t newCapacity)
    {

        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

        m_Size = (newCapacity < m_Size) ? newCapacity : m_Size;

        for (size_t i = 0; i < m_Size; i++) {

            // move operator does not work
            //newBlock[i] = std::move(m_Data[i]);

            // Move element's in place?
            new(&newBlock[i]) T(std::move(m_Data[i]));
        }

        for (size_t i = 0; i < m_Size; i++) {
            m_Data[i].~T();
        }

        //delete[] m_Data;
        //::operator delete(m_Data, m_Capacity * sizeof(T));
        ::operator delete(m_Data);
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

    /**
    * Initializes POD elements to a value within a range.
    *
    * @param start 
    * @param end
    * @param value
    */
    template<class Q = T> typename std::enable_if<std::is_pod<Q>::value>::type     
    fill_m_Data(size_t start, size_t end, const Q& value)
    {
        if (value == Q()) {
            size_t size = end - start;
            memset(m_Data + start, 0, size * sizeof(*m_Data));
            return;
        }

        for (size_t i = start; i < end; i++) {
            m_Data[i] = value;
        }
    }

    /**
    * Initializes non POD elements to a value within a range.
    *
    * @param start 
    * @param end
    * @param value
    */
    template<class Q = T> typename std::enable_if<!std::is_pod<Q>::value>::type 
    fill_m_Data(size_t start, size_t end, const Q& value) 
    {

        for (size_t i = start; i < end; i++) {
            // Placement operator
            new(&m_Data[i]) T(value);
        }        
    }

};

#endif