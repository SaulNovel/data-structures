#include <iostream>

namespace QuickSort {

/**
 * It picks an element as pivot and partitions the given array around 
 * the picked pivot. There are many different versions of quickSort that 
 * pick pivot in different ways. 
 * 1) Always pick first element as pivot.
 * 2) Always pick last element as pivot (implemented below)
 * 3) Pick a random element as pivot.
 * 4) Pick median as pivot.
 * 
 * The key process in quickSort is partition(). Target of partitions is, 
 * given an array and an element x of array as pivot, put x at its correct 
 * position in sorted array and put all smaller elements (smaller than x) 
 * before x, and put all greater elements (greater than x) after x. All this 
 * should be done in linear time.
 * 
*/
template<class T>
class QuickSort
{
public:

    QuickSort() {}
    
    void sort(T* data, const size_t size) {
        if (size < 2) { return; }

        int end = static_cast<int>(size) - 1;
        quickSort(data, 0, end);
    }

private:
    void quickSort(T* data, const int begin, const int end) {
                
        if (begin >= end) { return; }

        int pivotIdx = partition(data, begin, end);
        int endLeft = pivotIdx-1;
        int beginRight = pivotIdx+1;

        quickSort(data, begin, endLeft);
        quickSort(data, beginRight, end);
    }

    /**
    *  This function takes last element as pivot, places 
    * the pivot element at its correct position in sorted
    * array, and places all smaller (smaller than pivot)
    * to left of pivot and all greater elements to right
    * of pivot 
    */
    int partition(T* data, const int begin, const int end) {
        // starts pointing to the end, 
        // ends pointing to the last element swaped (pivot index)
        int idxPivot = end;
        const T& pivot = data[end];

        for (int i=end-1; i>=0; i--) {
            if (data[i] >= pivot) {
                std::swap(data[i], data[--idxPivot]);
            }
        }
        std::swap(data[end], data[idxPivot]);

        return idxPivot;
    }

};

}