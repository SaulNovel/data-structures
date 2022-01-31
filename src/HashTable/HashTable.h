#ifndef HASH_TABLE
#define HASH_TABLE

#include <utility>
#include <list>
#include <assert.h>
#include <type_traits>

namespace Hashing
{
    
template<class T1, class T2>
class HashTable {
public:
    HashTable(size_t size) {
        hashGroups_ = static_cast<int>(size);
        table_ = new std::list<Item>[size];
    }

    void insert(const T1& key, const T2& value) {
        int index = hashFunction(key);

        std::list<Item>& list = table_[index];
        // List empty -> insert item
        if (list.empty()) {
            list.push_back({key, value});
            return;
        }
        // List not empty & key found -> update the value
        for (Item& item : list) {
            if (item.first == key) {
                item.second = value;
                return;
            }
        }

        // List not empty & key not found -> insert item
        list.push_back({key, value});        
    }

    std::pair<T1, T2> remove(const T1& key) {
        int index = hashFunction(key);

        std::list<Item>& list = table_[index];

        for (auto  it = list.begin(); it != list.end(); it++) {
            if (it->first == key) {
                Item itemCopy = *it;
                list.erase(it);
                return itemCopy;
            }
        }
        std::string msg = "Element with key '" + std::to_string(key) + "' not found";
        throw std::runtime_error(msg);
    }

    T2 operator[](const T1& key) {
        int index = hashFunction(key);

        const std::list<Item>& list = table_[index];
        for (const Item& item : list) {
            if (item.first == key) {
                return item.second;
            }
        }

        // throw key does not exists?
        return T2();
    }

    const std::vector<T1> getKeys() {
        std::vector<T1> keys;
        for (int i=0; i<hashGroups_; i++) {
            for (const Item& item : table_[i]) {
                keys.push_back(item.first);
            }
        }

        return keys;
    }


    void printHasTable() {

        for (int i=0; i<hashGroups_; i++) {
            const std::list<Item>& list = table_[i];
            //std::cout << "number of lists at index '" << i << "': " << list.size() << std::endl; 
            for (const Item& item : list) {
                std::cout << "[" << item.first << "] = " << item.second << std::endl; 
            }
        }
    }

    ~HashTable() {
        delete[] table_;
    }

private:
    static constexpr bool validKeyTypes = std::is_same<T1, int>::value || std::is_same<T1, std::string>::value;
    static_assert(validKeyTypes && "Key types supported {int, std::string}");

    typedef std::pair<T1, T2> Item;

    int hashGroups_;
    std::list<Item>* table_;

    int hashFunction(const int key) {
        return hashGroups_ % key;
    }

    int hashFunction(const std::string& key) {
        int hashVal = 0;
        for (std::size_t i=0; i<key.size(); i++) {
            hashVal += key[i];
            hashVal = (hashVal * key[i]) % hashGroups_;
        }

        return hashVal;
    }

};

}

#endif
