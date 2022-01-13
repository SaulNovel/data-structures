#include <iostream>

namespace InsertionSort {

template<typename T>
int getShiftIdx(const T* data, int endIdx,  const T& element) {
    for (int i=0; i<=endIdx; i++) {
        if (element > data[i]) { 
            continue; 
        }
        return i;
    }
    return -1;
}

/**
 * Find minimum and switch to the first position
*/ 
template<typename T>
void sort(T* data, size_t size) {
    int length = static_cast<int>(size);

    if (length < 2) { return; }

    for (int i=1; i<length; i++) {

        // only sort number if previous number is bigger
        // This is the part of insertion sort that makes it fast if the array is almost sorted.
        if (data[i] > data[i-1]) { continue; }

        // compare current element with all previous elements to know where it needs to be inserted
        int shiftIdx = getShiftIdx(data, (i-1), data[i]);

        if (shiftIdx == -1) { continue; }

        // data[i] must be insterted at data[shiftIdx] 
        // shift all element 1 position in range [shiftIdx+1, i]
        const T current = data[i];
        for (int j=i; j>shiftIdx; j--) {
            data[j] = data[j-1];
        }
        data[shiftIdx] = current;
    }
}

}