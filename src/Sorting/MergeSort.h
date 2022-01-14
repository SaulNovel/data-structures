#include <iostream>
#include <cmath>

namespace MergeSort {

/**
 * Conceptually, a merge sort works as follows:
 * 1) Divide the unsorted list into n sublists, each containing one 
 *    element (a list of one element is considered sorted).
 * 2) Repeatedly merge sublists to produce new sorted sublists until 
 *    there is only one sublist remaining. This will be the sorted list.
 * 3) Merging of two lists done as follows:
 *    - The first element of both lists is compared. If sorting in ascending 
 *      order, the smaller element among two becomes a new element of the sorted list.
 *    - This procedure is repeated until both the smaller sublists are empty 
 *      and the newly combined sublist covers all the elements of both the sublists. 
 * 
 * O(logn)
*/
template<class T>
class MergeSort
{
public:

    MergeSort() {}
    
    void sort(T* data, const size_t size) {
        int end = static_cast<int>(size) - 1;
        this->mergeSort(data, 0, end);
    }

private:
    void mergeSort(T* data, const int begin, const int end) {

        // array contains 1 or 0 elements
        if (begin >= end) { 
            return; 
        }

        // divide the array in left/right recursively till begin == end ( array contains 1 element)
        int mid = begin + (end - begin) / 2;
        // uses the stack to store the subarrays
        //std::cout << "left:" << std::endl;
        //std::cout << "- section: {" << begin << ", " << end << "}" << std::endl;  

        mergeSort(data, begin, mid);
        //std::cout << "right:" << std::endl;
        //std::cout << "- section: {" << begin << ", " << end << "}" << std::endl;  

        mergeSort(data, (mid+1), end);
        // All subarrays are on the stack
        // Merge each subarray (return call)
        merge(data, begin, mid, end);

    }

    /**
    * Merge function
    * - time complexity: O(n)
    * - space complexity: O(n) in worst case
    * 
    * Recieves a poiter to the array, and 2 sections of the array:
    * - left section: [begin, mid]
    * - right section: [mid+1, end]
    * 
    * Allocates an array of size 'end' (dimension of the range checked)
    * Once the array is ordered, overwrites the orginal section of the array
    * 
    */ 
    void merge(T* data, const int begin, const int mid, const int end) {
    
        // std::cout << "begin: " << begin << " mid: " << mid << " end: " << end << std::endl;

        vector<T> merged;
        int size = end - begin + 1;
        merged.reserve(size);

        int leftIdx = begin;
        int rightIdx = mid + 1;

        // Merge the temp arrays back into array[left..right]
        for (int i=0; i<size; i++) {
            if (leftIdx > mid || rightIdx > end) {
                break;
            }

            if (data[leftIdx] <= data[rightIdx]) {
                merged.push_back(data[leftIdx]);
                leftIdx++;
                continue;
            }
            merged.push_back(data[rightIdx]);
            rightIdx++;
        }


        // left range [begin, mid]
        // right range [mid+1, end]
        if (leftIdx > mid) {
            append(merged, data, rightIdx, end);
        }

        if (rightIdx > end){
            append(merged, data, leftIdx, mid);
        }

        // Overwrite section of the array, loop range of merged array
        int arrIdx = begin;
        for (const T& value : merged) {
            data[arrIdx] = value;
            arrIdx++;
        }

        /**
        // Overwrite section of the array, range of original array
        int idx = 0;
        for (int i=begin; i<=end; i++) {
            std::cout << "merged[" << idx << "]:" << merged.at(idx) << std::endl;
            data[i] = merged.at(idx); 
            idx++;
        }

        std::cout << "merged -> ";
        for (int value : merged) {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        std::cout << "orginal -> ";
        for (int i=begin; i<=end; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
        */
    }

    void append(std::vector<T>& array, const T* data, const int begin, const int end) {
        for (int i=begin; i<=end; i++) {
            array.push_back(data[i]);
        }
    }

};

}