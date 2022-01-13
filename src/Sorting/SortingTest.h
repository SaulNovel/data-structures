#include <Sorting/BubbleSort.h>
#include <Sorting/SelectionSort.h>
#include <Sorting/InsertionSort.h>
#include <Sorting/MergeSort.h>
#include <Sorting/QuickSort.h>

#include <iostream>
#include <vector>

// Sorting interview questions:
//#1 - Sort 10 schools around your house by distance: insertion sort
// Correct answer: 

//#2 - eBay sorts listings by the current Bid amount: quick sort
// Correct answer: counting/radix sort (only integers within a range)

//#3 - Sport scores on ESPN: counting/radix sort
// Correct answer: quick sort (decimals)

//#4 - Massive database (can't fit all into memory) needs to sort through past year's user data: insertion sort
// Correct answer: Merge sort (since it cant fit into memory it will use an external one, massive data, worried about picking the wrong pivot -> quick sort discarded)

//#5 - Almost sorted Udemy review data needs to update and add 2 new reviews: insertion sort
// Correct answer: insertion sort

//#6 - Temperature Records for the past 50 years in Canada: quick sort
// Correct answer: 
// - Radix/counting sort if temperatures have no decimal places and within a range (integer number within small range)
// - quick sort

//#7 - Large user name database needs to be sorted. Data is very random. quick sort
// - Correct answer: merge sort (warranties O(nlogn) when there is not enough information moreover quick sort might be quadratic complexity if wrong pivot)
// - Quick sort if not too worry about the worst case

//#8 - You want to teach sorting for the first time: bubble/selection sort
// Correct answer: bubble/selection sort

/**
 * Quick sort -> average case performance matters more than worst case performance
 * Merge sort -> warranties O(nlogn) always, stable but takes O(n) space complexity
 * Insertion sort -> easy to implement, advantaje when data is almost ordered
 * 
 * Other algorithms:
 * - Heap Sort: https://brilliant.org/wiki/heap-sort/
 * - Quicksort vs heapsort: https://stackoverflow.com/questions/2467751/quicksort-vs-heapsort
 * - Radix Sort: https://brilliant.org/wiki/radix-sort/
 *               https://www.cs.usfca.edu/~galles/visualization/RadixSort.html
 * - Counting Sort: https://brilliant.org/wiki/counting-sort/
 *                  https://www.cs.usfca.edu/~galles/visualization/CountingSort.html
*/ 

namespace SortingTest {

template<typename T>
void printArr(const T* data, size_t size, bool sorted = true) {
    std::cout << (sorted ? "sorted" : "original") <<" array -> ";
    for (size_t i=0; i<size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


void bubbleSort_test() {
    std::vector<int> numbers = {99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0};
    BubbleSort::sort(numbers.data(), numbers.size());

    printArr(numbers.data(), numbers.size());

}

void selectionSort_test() {
    std::vector<int> numbers = {99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0};
    SelectionSort::sort(numbers.data(), numbers.size());

    printArr(numbers.data(), numbers.size());

}

void insertionSort_test() {
    std::vector<int> numbers = {99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0};
    InsertionSort::sort(numbers.data(), numbers.size());

    printArr(numbers.data(), numbers.size());

    std::vector<int> numbers2 = {29, 100, 99, -1, 99, 100, 200, 30};
    InsertionSort::sort(numbers2.data(), numbers2.size());

    printArr(numbers2.data(), numbers2.size());
}

void mergeSort_test() {
    std::vector<int> numbers = {99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0};

    printArr(numbers.data(), numbers.size(), false);

    MergeSort::MergeSort<int> mergeSort;
    mergeSort.sort(numbers.data(), numbers.size());

    printArr(numbers.data(), numbers.size());

}

void quickSort_test() {
    std::vector<int> numbers = {99, 44, 6, 2, 1, 5, 63, 87, 283, 4, 0};
    //std::vector<int> numbers = {10, 80, 30, 90, 40, 90, 70};

    printArr(numbers.data(), numbers.size(), false);

    QuickSort::QuickSort<int> quickSort;
    quickSort.sort(numbers.data(), numbers.size());

    printArr(numbers.data(), numbers.size());

}


void test() {
    //bubbleSort_test();
    //selectionSort_test();
    //insertionSort_test();
    //mergeSort_test();
    quickSort_test();
}

}