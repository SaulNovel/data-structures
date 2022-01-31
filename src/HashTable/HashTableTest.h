#include <Hashtable/HashTable.h>
#include <Hashtable/FirstRecurringCharacter.h>

#include <iostream>

namespace HashTableTest
{

    void testCustomHasSet() {

        using Hashing::HashTable;
        HashTable<std::string, int> hashTable(10);

        hashTable.insert("Jacob", 29);
        hashTable.insert("Kate", 27);
        hashTable.insert("Mpho", 25);
        hashTable.insert("Sarah", 21);
        hashTable.insert("Edna", 22);
        hashTable.insert("Maren", 23);
        hashTable.insert("Eliza", 24);
        hashTable.insert("Robert", 26);
        hashTable.insert("Jane", 28);

        int number = hashTable["Mpho"];
        std::cout << "Mpho: " << number << std::endl;

        // Element not found -> number=0
        number = hashTable["George"];
        std::cout << "George: " << number << std::endl;

        hashTable.printHasTable();

        std::cout << "Keys -> ";
        for (const auto &key : hashTable.getKeys())
        {
            std::cout << key << " ";
        }
        std::cout << std::endl;

        std::cout << "HasTable after removing some elements: " << std::endl;

        hashTable.remove("Jane");
        hashTable.remove("Robert");
        hashTable.remove("Eliza");
        // Try removing element which does not exists
        hashTable.remove("George");

        hashTable.printHasTable();

        std::cout << "Keys -> ";
        for (const auto &key : hashTable.getKeys())
        {
            std::cout << key << " ";
        }
        std::cout << std::endl;
        
        {
        HashTable<int, float> hashTable(10);
        // Test key type not suppoted
        // HashTable<float, float> hashTable2(10);
        }

    }

    void test() {

        FirstRecurringCharacter::test();


    }

}