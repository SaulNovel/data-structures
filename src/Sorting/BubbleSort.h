#include <iostream>

namespace BubbleSort {

/**
 * Bubble up highest number one by one
*/ 
template<typename T>
void sort(T* data, size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        size_t maxIdx = 0;
        for (size_t j = 1; j < size; j++)
        {
            if (data[maxIdx] > data[j])
            {
                std::swap(data[maxIdx], data[j]);
            }
            maxIdx = j;
        }
    }
}

}