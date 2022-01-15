#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

namespace ContainsCommonItems 
{

typedef std::vector<char> InputType;

/**
 * Nested loop: brute force -> O(n1*n2)
*/
bool nestedLoop(const InputType& array1, const InputType& array2) { //  O(n^2)
    for (const char element1 : array1) {
        for (const char element2 : array2) {
            if (element1 == element2) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Helper function to convert values from array to HasSet
 * @returns arrayElements
*/
const std::unordered_set<char> mapArrToHasSet(const InputType& array) {
    std::unordered_set<char> arrayElements;
    for (const char element : array) {
        arrayElements.emplace(element);
    }

    return arrayElements; // RVO
}

/**
 * Use a hasSet to keep the elements viewed from array1
 * Time complexity: O(n1 + n2)
 * Space complexity: O(n1)
 * - hasSet inserts/emplace -> complexity: O(1) in average
 * - hastSet count/find -> complexity: O(1) in average
 * Iterate array2 and for each element check if contained in hasSet
*/
bool hasTable(const InputType& array1, const InputType& array2) { //  O(n1 + n2)

    if (array1.empty() || array2.empty()) {
        return false;
    }   

    const std::unordered_set<char> viewedElements = mapArrToHasSet(array1);

    for (const char element : array2) {
        if (viewedElements.count(element)) {
            return true;
        }
    }
    return false;
}

/**
 * Sorting O(logn) and comparing O(n) -> O(logn*n)
 * Iterate the largest array:
 * - Take first element for both arrays, compare them:
 * - if equal -> return/move to next element 
 * - if not -> take the biggest element and iterate the other array till find an element equal or greater
 * Sorting algorithm for large amount of data, requirements:
 * - Time complexity < n^2 (better than "nestedLoop" solution)
 * - Space complexity < O(n) (better than "hasTable" solution)
*/
bool sortingAndLoop(const InputType& array1, const InputType& array2) {
    // Sort array1 O(n1*logn1)
    // Sort arra2 O(n2*logn2)

    // comparison should be O(n1) or O(n2) (the sortest)

    // O(n1*logn1 + n2*logn2 + O(n1)) -> O(n1*logn1 + n2*logn2) better than O(n^2)
    return false;
}

/**
 * Given 2 arrays, create a function that let's a user know 
 * (true/false) whether these 2 arrays contain any common items 
 * For example:
 * - {'a', 'b', 'c', 'x'}
 * - {'w', 'q'}
 *   -> Should return false
 * - {'a', 'b', 'c', 'x'}
 * - {'z', 'y', 'x'}
 *   -> Should return true
 * 
 * Key questions:
 * - what is more important time complexity or space complexity?
 *   -> Possible answer: assuming the array can get very very large, they want the best possible solution
*/
void test() 
{
    const InputType array1 = {'a', 'b', 'c', 'x'};
    const InputType array2 = {'z', 'y', 'x'};
    const InputType array3 = {'w', 'q'};

    std::cout << hasTable(array1, array2) << std::endl;
    std::cout << hasTable(array1, array3) << std::endl;

}

}