#include <iostream>
#include <array>
#include<string>
#include<vector>
#include<math.h>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<type_traits>

// collection of numbers
// find a matching pair that is equal to a given sum
//

// example:
// - [1, 2, 3, 9] = 8 NO
// - {1, 2, 4, 4} = 8

namespace MatchingPairs
{
    
typedef std::pair<uint32_t, std::vector<std::string>> ReturnType;
typedef std::pair<int32_t, std::set<std::string>> ElementsViewed;

/*** Common funtions ***/
template<typename T>
void printMatchingPairs(const T& entry) {

    bool constexpr validTypesCheck = std::is_same<T, ReturnType>::value || std::is_same<T, ElementsViewed>::value;
    static_assert(validTypesCheck, "Valid types: ReturnType/ElementsViewed");

    std::cout << "-------------------------------" << std::endl;
    std::cout << "number of pairs found: " << entry.first << std::endl;
    if (entry.second.empty()) {
        return;
    }

    std::cout << "pairs:" << std::endl;
    for (const auto& pair : entry.second) {
        std::cout << " - {" << pair << "}" << std::endl;
    }
}

/*** Common funtions end ***/


/*** First try: brute force -> O(n^2) ***/
/**
 * Finds 2 elements (x1, x2) within an array which satifies the condition:
 * - x1 + x2 = sum
 * @param sequence array of numbers
 * @param sum  
 * N, array size
*/
template<std::size_t N>
const ReturnType solution1(const std::array<int32_t, N>& sequence, int32_t sum) {
    std::vector<std::string> matchingPairs;
    uint32_t pairsCounter=0;

    for (int32_t index=(sequence.size()-1); index>0; index--) { //O(n)

        int32_t element1 = sequence.at(index);
        if (element1 >= sum) {
            continue;
        }

        for (int32_t nestedIndex=(index-1); nestedIndex>=0; nestedIndex--) { //O(n)
            int32_t element2 = sequence.at(nestedIndex);
            bool matchingPair = (element1 + element2) == sum;

            if (!matchingPair) {
                continue;
            }

            pairsCounter++;
            matchingPairs.push_back(std::to_string(element1) + " + " + std::to_string(element2) + " = " + std::to_string(sum));
        }
    } 

    return std::make_pair(pairsCounter, matchingPairs);
}
/*** First try End ***/


/*** Second try: iterative iterative + binary search -> O(n*logn) ***/
/**
 * Binary search implementation for an int32_t array 
 * True if element exist in array
 * Simplest cases:
 * - (start > end) || (end < 0) -> wrong input
 * - start == end -> 1 element to check
  * @param array int32_t array
  * @param start 
  * @param end 
  * @param element
*/
bool isFound(const int32_t* array, int32_t start, int32_t end, int32_t element) {
    if ((start > end) || (end < 0) || (array == nullptr)) { 
        return false; 
    }

    if (start == end) {
        return (array[start] == element); 
    }

    int32_t middle = static_cast<int32_t>(std::floor((end+start)/2));
    if (array[middle] == element) { return true; }

    int32_t leftStart = start;
    int32_t leftEnd = middle;
    int32_t rightStart = middle+1; // middle=0 -> rightStart=1
    int32_t rightEnd = end;

    // Recursive call
    return (array[middle] < element) ? isFound(array, rightStart, rightEnd, element) :
        isFound(array, leftStart, leftEnd, element);
}

/**
 * Iterative * Binary search -> Goal: O(n*logn)
 * Finds 2 elements (x1, x2) within an array which satifies the condition:
 * - x1 + x2 = sum
 * - negatives could happen
 * @param sequence array of numbers
 * @param sum  
 * N, array size
*/
template<std::size_t N>
const ReturnType solution2(const std::array<int32_t, N>& sequence, int32_t sum) {
    std::vector<std::string> matchingPairs;
    uint32_t pairsCounter=0;

    int32_t startIdx = sequence.size()-1;
    for (int32_t index=startIdx; index>0; index--) { // O(n)

        int32_t element1 = sequence.at(index);
        //if (element1 >= sum) { continue; } // allows only positive solutions

        int32_t expected = sum - element1;

        // Elements sorted in ascending order: expected element can only be in the range {0, index-1}
        bool found = isFound(sequence.data(), 0, (index-1), expected); // O(logn)
        if (!found) { continue; }

        pairsCounter++;
        matchingPairs.push_back(std::to_string(element1) + " + " + std::to_string(expected) + " = " + std::to_string(sum)); // O(1)
    }

    return std::make_pair(pairsCounter, matchingPairs);
}
/*** Second try End ***/

// Binary search is unidirectional, seems still slow for the solution

/*** Recursive solution keeping 2 indexes -> O(n)***/
/**
 * Sum pairs: Goal: O(n)
 * - Expect an ascending ordered array as input
 * - 2 indexes, start by last element and first element
 * - The array always shrinks at least one element:
 *   -> array[start] + array[end] < sum -> start++
 *   -> array[start] + array[end] > sum -> end--
 *   -> array[start] + array[end] == sum -> pair found, start++, end--
 *   -> stop when start >= end
 * Take next number and repeat operation above
  * @param array int32_t array
  * @param start 
  * @param end 
  * @param sum
  * @param retVal data structure to represent the result
*/
void solution3(const int32_t* array, int32_t start, int32_t end, int32_t sum, ReturnType& retVal) { // O(n)

    // {1, 2, 4, 4}

    if ((start >= end) || (array[start] > sum) || (end < 0)) {
        return;
    }

    int32_t last = array[end];
    int32_t first = array[start];
    
    int32_t result = last + first;

    std::cout << "first: " << first << " last: " << last << std::endl;

    // leave it here, in case first<=0 it will work
    if (result == sum) {
        //std::cout << "matching pairs found" << std::endl;

        retVal.first++;
        retVal.second.push_back(std::to_string(last) + " + " + std::to_string(first) + " = " + std::to_string(sum));
        solution3(array, ++start, end, sum, retVal); // O(n)
    }

    /**
     * last is the highest value, we can only decrease end
     * first is the lowest value, we can only increase start
     *  
    */
    else if (result < sum) {
        //std::cout << "increasing start" << std::endl;

        solution3(array, ++start, end, sum, retVal); // O(n)
    }

    /**
     * result > sum
     * even if:
     * - last > sum
     * - first < 0
     * - we are sure that result > sum
     * - increasing start will only give greater results
    */
    else {
        //std::cout << "decreasing end" << std::endl;
 
        solution3(array, start, --end, sum, retVal); // O(n)
    }
}

void TestSolution3(const int32_t* data, size_t size, int32_t sum) {
    ReturnType retVal;
    int32_t first = 0;
    int32_t end = static_cast<int32_t>(size-1);
    solution3(data, first, end, sum, retVal);
    printMatchingPairs(retVal);
}

/*** Third try End ***/

/*** Solution keeping 2 indexes and no sorted array -> O(n)***/
// No warranties that the array is sorted -> unordered_map (HasMap)?

bool isKeyFound(const std::unordered_map<int32_t, int32_t>& elements, int32_t key) {
    try {
        elements.at(key); // O(1)
        return true;
    } catch (const std::out_of_range& e) {
        //std::cout << "exception: '" << e.what() << "', (element '" << key << "' not found)" << std::endl;
        return false;
    }
}

void updateMatchingPairs(ReturnType& matchingPairs, const std::pair<int32_t, int32_t>& entry, int32_t val1, int32_t sum) {
    int32_t complement = entry.first;
    // Indicates how many times appeared the complement (key in the map)
    int32_t complementCounter = entry.second;
    matchingPairs.first += complementCounter;
    matchingPairs.second.push_back(std::to_string(val1) + " + " + std::to_string(complement) + " = " 
    + std::to_string(sum) + " repeated " + std::to_string(complementCounter) + " times");
}

/**
 * If key not found inserts pair {key, 1}
 * If key found increases key counter
*/
void insertMapEntry(std::unordered_map<int32_t, int32_t>& elements, int32_t key) {
    bool keyFound = isKeyFound(elements, key);
    keyFound ? (elements[key] += 1) : (elements[key] = 1); // O(1)
}

/**
 * Sum pairs: Goal: O(n)
 * - Keeps checked elements as keys in an unordered_map
 * @param array int32_t array
 * @param start 
 * @param end 
 * @param sum
 * @param retVal data structure to represent the result
*/
template<int32_t N>
const ReturnType solution4(const std::array<int32_t, N>& array, int32_t sum) { // O(n)

    ReturnType retVal;
    std::unordered_map<int32_t, int32_t> mapOfCheckedElement;

    int32_t start = 0;
    int32_t end = static_cast<int32_t>(array.size())-1;

    while(start < end) {
        
        int32_t last = array[end];
        int32_t first = array[start];

        //std::cout << "start: " << start << " end: " << end << std::endl;
        //std::cout << "first: " << first << " last: " << last << std::endl;

        if ((last + first) == sum) {
            const std::pair<int32_t, int32_t> entry = {last, 1}; 
            updateMatchingPairs(retVal, entry, first, sum);
        }

        else {
            // Check if the complement was previously added to the hasMap
            int32_t leftComplement = sum - first;
            if (isKeyFound(mapOfCheckedElement, leftComplement)) {
                const std::pair<int32_t, int32_t> entry = {leftComplement, mapOfCheckedElement[leftComplement]}; 
                updateMatchingPairs(retVal, entry, first, sum);
            }
            int32_t rightComplement = sum - last;
            if (isKeyFound(mapOfCheckedElement, rightComplement)) {
                const std::pair<int32_t, int32_t>& entry = {rightComplement, mapOfCheckedElement[rightComplement]};                 
                updateMatchingPairs(retVal, entry, last, sum);
            }
        }

        // TODO: this does not allow duplicates
        // store keys with a patternm? -> filter the element from the key and compare with the complement

        insertMapEntry(mapOfCheckedElement, first);
        insertMapEntry(mapOfCheckedElement, last);

        start++;
        end--;
        // TODO: improve moving end also
    }
    
    /*
    for (const auto& entry : mapOfCheckedElement) {
        std::cout << "hey: " << entry.first << " value: " << entry.second << std::endl;
    }
    */

    return retVal;
}
/*** Fourth try End ***/


/*** Solution Using a unordered_set, keeps elements, not the complement, problem if there are repeated elements -> O(n)***/
typedef std::unordered_set<int32_t> ElementHolderType;
void updateMatchingPairs(ElementsViewed& matchingPairs, int32_t val1, int32_t val2, int32_t sum) {
    matchingPairs.first += 1;

    const std::string orderedCoeff = (val1 > val2) ? (std::to_string(val1) + " + " + std::to_string(val2)) : (std::to_string(val2) + " + " + std::to_string(val1));
    matchingPairs.second.emplace((orderedCoeff + " = " + std::to_string(sum)));
}

void checkCompAndUpdateMatchinPairs(const ElementHolderType& elementsHolder, int32_t value, int32_t sum, ElementsViewed& matchingPairs) {
    int32_t complement = sum - value;
    if (elementsHolder.count(complement) > 0) {
        updateMatchingPairs(matchingPairs, complement, value, sum);
    }
}

/**
 * Sum pairs: Goal: O(n)
 * - Keeps checked elements as keys in an unordered_map
 * - This solution does not provide the number of duplicated sums if applied
 * @param array int32_t array
 * @param size 
 * @param sum
 * @param retVal data structure to represent the result
*/
const ElementsViewed solution(const int32_t* array, int32_t size, int32_t sum, ElementHolderType& elementsHolder) { // O(n)

    ElementsViewed retVal;
    int32_t start = 0;
    int32_t end = size-1;

    while(start < end) {
        
        int32_t last = array[end];
        int32_t first = array[start];

        if ((last + first) == sum) {
            updateMatchingPairs(retVal, last, first, sum);
        }

        else{
            // Check if the complement was previously added to the hasMap
            checkCompAndUpdateMatchinPairs(elementsHolder, first, sum, retVal);

            checkCompAndUpdateMatchinPairs(elementsHolder, last, sum, retVal);
        }

        elementsHolder.emplace(first);
        elementsHolder.emplace(last);

        start++;
        end--;
    }

    if (start == end) {
        int32_t value = array[start];
        checkCompAndUpdateMatchinPairs(elementsHolder, value, sum, retVal);
        elementsHolder.emplace(value);
    }
    return retVal;
}

// Binary search is unidirectional, seems still slow for the solution
// No warranties that the array is sorted

/** Solution proposed:
 * - Solution proposed: instead of inserting the keys, insert the complement
 * - Use data structure which is good for lookups
 * - HasTable has constant time for lookup
 *   -> we do not need to store any payload
 *   -> we need a HasSet in c++: std::unordered_set
 * - case of repeated elements
 * - when you are at an index, only look at the indexes before
 *   -> as long as checking before inserting things, that should work
*/

// Question: would you do something different if there were 10 million elements in the array?
// Large input: it does not fit in memory
// -> if the set fits in memory
// -> if hole input does not fit in memory
void solutionReducer(const int32_t* array, int32_t size, int32_t sum) {

    if (array == nullptr) {
        std::cout << "Invalid pointer" << std::endl;
        return;
    }

    const int32_t inputSize = 3;

    ElementsViewed retValTotal;
    std::unordered_set<int32_t> elementsHolder;

    // take a sub sequence of size "inputSize"
    // This will give either max number of iterations if result is an integer, or max number of iterations -1 if not
    int32_t iterations = static_cast<int32_t>(std::ceil(size/inputSize));

    // from 0 to the previous of last iteration, (last iteration - 1)
    for (int32_t i=0; i<iterations; i++) {
        int32_t start = i*inputSize;

        //std::cout << "start: " << start << std::endl;
        //std::cout << "end: " << start + inputSize -1 << std::endl;

        const ElementsViewed retVal = solution(array + start, inputSize, sum, elementsHolder);
        retValTotal.first += retVal.first;
        // appeding vector at the end of another vector
        retValTotal.second.insert(retVal.second.begin(), retVal.second.end());
    }

    // Last iteration
    int32_t lastSubSeqSize = size - (inputSize * iterations);
    if (lastSubSeqSize > 0) {        
        int32_t start = inputSize * iterations;        
        const ElementsViewed retVal = solution(array + start, lastSubSeqSize, sum, elementsHolder);

        retValTotal.first += retVal.first;
        // appeding vector at the end of another vector
        retValTotal.second.insert(std::begin(retVal.second), std::end(retVal.second));
    }

    printMatchingPairs(retValTotal);
}

/*** Fifth try End ***/

/** Solution proposed:
 * - Solution proposed: instead of inserting the keys, insert the complement
 * - Use data structure which is good for lookups
 * - HasTable has constant time for lookup
 *   -> we do not need to store any payload
 *   -> we need a HasSet in c++: std::unordered_set
 * - case of repeated elements
 * - when you are at an index, only look at the indexes before
 *   -> as long as checking before inserting things, that should work
*/

void test()
{
// - {1, 2, 4, 4} = 8
    
    /*
    const std::array<int32_t, 4> sequence = {1, 2, 4, 4};
    const std::array<int32_t, 4> sequence2 = {-1, 2, 3, 9};
    const std::array<int32_t, 8> sequence3 = {-100, -99, -20, 2, 3, 9, 98, 120};

    TestSolution3(sequence.data(), sequence.size(), sum);

    TestSolution3(sequence2.data(), sequence2.size(), sum);

    TestSolution3(sequence2.data(), sequence2.size(), 100);

    TestSolution3(sequence3.data(), sequence3.size(), 100);


    printMatchingPairs(solution2(sequence, 6));
    printMatchingPairs(solution2(sequence, 3));
    
    printMatchingPairs(solution2(sequence2, 8));
    printMatchingPairs(solution2(sequence2, 10));
    printMatchingPairs(solution2(sequence2, 12));



    printMatchingPairs(solution4<sequence_non_sorted.size()>(sequence_non_sorted, 8));
    printMatchingPairs(solution4<sequence2_non_sorted.size()>(sequence2_non_sorted, 8));
    printMatchingPairs(solution4<sequence2_non_sorted.size()>(sequence2_non_sorted, 100));
    printMatchingPairs(solution4<sequence3_non_sorted.size()>(sequence3_non_sorted, 100));
    printMatchingPairs(solution4<sequence4_non_sorted.size()>(sequence4_non_sorted, 8));

    std::array<int32_t, 0> emptyArray;
    printMatchingPairs(solution4<emptyArray.size()>(emptyArray, 8));
    */

    const std::array<int32_t, 4> sequence_non_sorted = {2, 4, 1, 4};
    const std::array<int32_t, 4> sequence2_non_sorted = {3, 9, -1, 2};
    const std::array<int32_t, 8> sequence3_non_sorted = {98, 9, -20, 120, 3, -99, -100, 2};
    const std::array<int32_t, 12> sequence4_non_sorted = {9, 9, 9, 1, 2, 0, -1, 1, 3, 1, 9, 9};
    const std::array<int32_t, 0> emptyArray;

    solutionReducer(sequence_non_sorted.data(), static_cast<int32_t>(sequence_non_sorted.size()), 8);
    solutionReducer(sequence2_non_sorted.data(), static_cast<int32_t>(sequence2_non_sorted.size()), 8);
    solutionReducer(sequence2_non_sorted.data(), static_cast<int32_t>(sequence2_non_sorted.size()), 100);
    solutionReducer(sequence3_non_sorted.data(), static_cast<int32_t>(sequence3_non_sorted.size()), 100);
    solutionReducer(sequence4_non_sorted.data(), static_cast<int32_t>(sequence4_non_sorted.size()), 8);

    // Invalid pointers
    solutionReducer(emptyArray.data(), static_cast<int32_t>(emptyArray.size()), 8);
    solutionReducer(nullptr, 5, 8);

    /**
     * Solution for raw pointer validation:
     * - Helper function (wrapper)
     * - Helper function is a template which only admits certain data structures
     * - use consexpr and std::is_same to handle errors at compilation time or std::enable_if
    */

    std::cout << "Hello" << std::endl;

}

}