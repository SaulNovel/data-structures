#include <iostream>
#include <array>

// collection of numbers
// find a matching pair that is equal to a given sum
//

// example:
// - [1, 2, 3, 9] = 8 NO
// - {1, 2, 4, 4} = 8

namespace MergeSortedArrays
{


/*** Iterative solution -> O(n1 + n2) ***/
template<size_t N1, size_t N2> 
void addElementsLeft(std::array<int32_t, N1>& output, size_t outputIdx, const std::array<int32_t, N2>& array, size_t arrayIdx) {

    int32_t elementsToInsert = static_cast<int32_t>(array.size() - arrayIdx);
    if (elementsToInsert <= 0) {
        // Nothing to be done
        return;
    }

    size_t end = outputIdx + elementsToInsert;
    //std::cout << "end: " << end << std::endl;

    // TODO: Things that can go wrong (only for debugging)
    if(end != output.size()) {
        return;
    }

    //std::cout << "elementsToInsert: " << elementsToInsert << std::endl;
    //std::cout << "output start: " << outputIdx << std::endl;
    //std::cout << "output end: " << end << std::endl;

    for (size_t i=outputIdx; i<end; i++) {
        output[i] = array[arrayIdx];
        arrayIdx++;
    }
}

/**
 * Create a function that reverses a string 
 * - input: [0, 3, 4, 31], [4, 6, 30]
 * - output: [0, 3, 4, 4, 6, 30, 31]
 * 
 * Example:
 * - 0 <= 4 -> yes -> 0 array1It++
 * - 3 <= 4 -> yes -> 3 array1It++
 * - 4 <= 4 -> yes -> 4 array1It++
 * - 31 <=4 -> no -> 4 (array2) array2It++
 * 
 * Complexity is O(n1 + n2)
 * 
*/
template<size_t N1, size_t N2>
const std::array<int32_t, (N1+N2)> mergeSortedArrays(const std::array<int32_t, N1>& array1, const std::array<int32_t, N2>& array2) {
    const size_t outputSize = N1 + N2;
    std::array<int32_t, outputSize> output;

    /** TODO: make it work, seems it needs to copy it anyway
    if (array2.size() == 0) {
        return array1; 
    }
    if (array1.size() == 0) {
        return array2;
    }
    **/

    size_t array1It = 0;
    size_t array2It = 0;
    for (size_t i=0; i<output.size(); i++) {
        
        //std::cout << "array1It: " << array1It << ", array2It: " << array2It << std::endl;
        // One of the arrays reached it end, copy what is left from the other
        if (array1It >= array1.size()) {
            // copy what is left from array2 and break
            addElementsLeft(output, i, array2, array2It);
            break;
        }
        if (array2It >= array2.size()) {
            //std::cout << "addElementsLeft" << std::endl;
            // copy what is left from array1 and break
            addElementsLeft(output, i, array1, array1It);
            break;
        }

        if (array1[array1It] <= array2[array2It]) {
            output[i] = array1[array1It];
            array1It++;
        }
        else {
            output[i] = array2[array2It];
            array2It++;
        }
    }

    return output;
}
/*** Iterative solution end ***/

/*** Recursive solution -> O(n1 + n2) ***/
template<size_t N1, size_t N2> 
void addElementsLeftRecursive(const std::array<int32_t, N1>& array, int32_t arrayIdx, std::array<int32_t, N2>& output) {

    // trivial case
    if (arrayIdx < 0) {
        return;
    }

    output[arrayIdx] = array[arrayIdx];
    arrayIdx--;

    return addElementsLeftRecursive(array, arrayIdx, output);
}

template<size_t N1, size_t N2, size_t N3>
void mergeSortedArraysRecursive(const std::array<int32_t, N1>& array1, int32_t array1Idx, const std::array<int32_t, N2>& array2, int32_t array2Idx, std::array<int32_t, N3>& output, int32_t outputIdx) {

    std::cout << "array2Idx: " << array2Idx << " -> array1Idx: " << array1Idx << " -> outputIdx: " << outputIdx << std::endl;

    // simplest case
    if (array1Idx < 0) {
        std::cout << "array2[array2Idx]: " << array2[array2Idx] << std::endl;
        return addElementsLeftRecursive(array2, array2Idx, output);
    }

    if (array2Idx < 0) {
        std::cout << "array1[array1Idx]: " << array1[array1Idx] << std::endl;
        return addElementsLeftRecursive(array1, array1Idx, output);
    }

    if (array1[array1Idx] >= array2[array2Idx]) {
        output[outputIdx] = array1[array1Idx];
        array1Idx--;
        outputIdx--;
        return mergeSortedArraysRecursive(array1, array1Idx, array2, array2Idx, output, outputIdx);
    }

    output[outputIdx] = array2[array2Idx];
    array2Idx--;
    outputIdx--;
    return mergeSortedArraysRecursive(array1, array1Idx, array2, array2Idx, output, outputIdx);
}
/*** Recursive solution end ***/



void printArray(const int32_t* array, size_t size) {
    std::cout << "size: [ ";
    for (size_t i=0; i<size; i++) {
        std::cout << array[i] << " "; 
    }
    std::cout << "]" << std::endl;
}

void test() {

{
    const std::array<int32_t, 4> array1 = {0, 3, 4, 31};
    const std::array<int32_t, 3> array2 = {4, 6, 30};

    const auto output = mergeSortedArrays<array1.size(), array2.size()>(array1, array2);
    printArray(output.data(), output.size());
}

{
    const std::array<int32_t, 8> array1 = {0, 3, 4, 31, 99, 100, 100, 100};
    const std::array<int32_t, 3> array2 = {4, 6, 30};

    const auto output = mergeSortedArrays<array1.size(), array2.size()>(array1, array2);
    printArray(output.data(), output.size());
}

{
    const std::array<int32_t, 9> array1 = {-3, 0, 3, 4, 31, 99, 100, 100, 100};
    int32_t array1Idx = static_cast<int32_t>(array1.size() - 1);

    const std::array<int32_t, 5> array2 = {-2, -1, 4, 6, 30};
    int32_t array2Idx = static_cast<int32_t>(array2.size() - 1);

    std::array<int32_t, array1.size() + array2.size()> output;
    int32_t outputIdx = static_cast<int32_t>(output.size() - 1);
    mergeSortedArraysRecursive(array1, array1Idx, array2, array2Idx, output, outputIdx);
    printArray(output.data(), output.size());
}

}

}