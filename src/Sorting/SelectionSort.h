#include <iostream>

namespace SelectionSort {

/**
 * Find minimum and switch to the first position
*/ 
template<typename T>
void sort(T* data, size_t size) {
    for (size_t i=0; i<size; i++) {
        // find minimum
        size_t minIdx = i;
        for (size_t j=(i+1); j < size; j++) {
            if (data[j] < data[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(data[minIdx], data[i]);
    }
}

}