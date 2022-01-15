#include <iostream>
#include <array>
#include<string>
#include<vector>
#include<set>
#include<unordered_set>

// collection of numbers
// find a matching pair that is equal to a given sum
//

// example:
// - [1, 2, 3, 9] = 8 NO
// - {1, 2, 4, 4} = 8

namespace MatchingPairsSolution
{

class MatchingPairs
{

private:
    typedef std::pair<int32_t, std::vector<std::string>> MatchingPairsType;
    typedef std::unordered_set<int32_t> ElementHolderType;

    inline static void printMatchingPairs(const MatchingPairsType &entry)
    {

        std::cout << "---SEQUENCE OUTPUT---" << std::endl;
        std::cout << "number of pairs found: " << entry.first << std::endl;
        if (entry.second.empty()) {
            std::cout << "---------------------" << std::endl << std::endl;
            return;
        }

        std::cout << "pairs:" << std::endl;
        for (const auto &pair : entry.second)
        {
            std::cout << " -> {" << pair << "}" << std::endl;
        }
        std::cout << "---------------------" << std::endl << std::endl;
    }

    inline static void updateMatchingPairs(MatchingPairsType& matchingPairs, int32_t val1, int32_t val2, int32_t sum) {
        matchingPairs.first += 1;
        matchingPairs.second.push_back(std::to_string(val1) + " + " + std::to_string(val2) + " = " + std::to_string(sum));
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
    inline static const MatchingPairsType solution(const int32_t *array, int32_t size, int32_t sum, ElementHolderType &elementsHolder)
        { // O(n)

        MatchingPairsType matchingPairs;
        int32_t start = 0;
        int32_t end = size - 1;

        while (start <= end) {

            int32_t element = array[start];
            int32_t complement = sum - element;

            //std::cout << "element: " << element << " complement:" << complement << std::endl;

            // Check if this complement exist
            if (elementsHolder.count(element) > 0) {
                updateMatchingPairs(matchingPairs, complement, element, sum);
            }

            elementsHolder.emplace(complement);
            start++;
        }

        return matchingPairs;
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
    inline static void solutionReducer(const int32_t *array, int32_t size, int32_t sum)
    {

        if (array == nullptr)
        {
            std::cout << "Invalid pointer" << std::endl << std::endl;
            return;
        }

        const int32_t inputSize = 3;

        MatchingPairsType matchingPairsTotal;
        std::unordered_set<int32_t> elementsHolder;

        // take a sub sequence of size "inputSize"
        // This will give either max number of iterations if result is an integer, or max number of iterations -1 if not
        int32_t iterations = static_cast<int32_t>(ceil(static_cast<double>(size) / inputSize));

        // array size = 10
        // inputSize = 3
        // 10/3=4
        // iteration -> 0, 1, 2, 3
        // start     -> 0, 3, 6, 9
        // size      -> 3, 3, 3, 1

        // array size = 6
        // inputSize = 3
        // 6/3=2
        // iteration -> 0, 1
        // start     -> 0, 3
        // size      -> 3, 3

        // array size = 2
        // inputSize = 3
        // 2/3=1
        // iteration -> 0
        // start     -> 0
        // size      -> 2 (2 - 3*0)

        // lst it size = size - start*i

        // from 0 to the previous of last iteration, (last iteration - 1)
        for (int32_t i = 0; i < iterations; i++)
        {
            int32_t start = i * inputSize;
            int32_t seqSize = (i == iterations-1) ? (size - start) : inputSize;

            //std::cout << "start: " << start << std::endl;
            //std::cout << "end: " << start + inputSize -1 << std::endl;

            const MatchingPairsType matchingPairs = solution(array + start, seqSize, sum, elementsHolder);
            matchingPairsTotal.first += matchingPairs.first;
            // appeding vector at the end of another vector
            matchingPairsTotal.second.insert(matchingPairsTotal.second.end(), matchingPairs.second.begin(), matchingPairs.second.end());
        }

        printMatchingPairs(matchingPairsTotal);
    }

public:
    template <typename T>
    static void solutionInvoker(const T &input, int32_t sum)
    {
        constexpr bool vectorType = std::is_same<std::vector<int32_t>, T>::value;
        static_assert(vectorType, "Solution only admits vector's/array's of integers");
            
        int32_t size = static_cast<int32_t>(input.size());
        solutionReducer(input.data(), size, sum);
    }

    template <size_t N>
    static void solutionInvoker(const std::array<int32_t, N>& input, int32_t sum)
    {

        int32_t size = static_cast<int32_t>(input.size());
        solutionReducer(input.data(), size, sum);
    }
};

void test()
{
// - {1, 2, 4, 4} = 8
    
    const std::array<int32_t, 4> sequence_non_sorted = {2, 4, 1, 4};
    const std::array<int32_t, 4> sequence2_non_sorted = {3, 9, -1, 2};
    const std::vector<int32_t> sequence3_non_sorted = {98, 9, -20, 120, 3, -99, -100, 2};
    const std::array<int32_t, 12> sequence4_non_sorted = {9, 9, 9, 1, 2, 0, -1, 1, 3, 1, 9, 9};
    const std::array<int32_t, 0> emptyArray;

    MatchingPairs::solutionInvoker<sequence_non_sorted.size()>(sequence_non_sorted, 8);
    MatchingPairs::solutionInvoker<sequence_non_sorted.size()>(sequence_non_sorted, 100);
    MatchingPairs::solutionInvoker<sequence2_non_sorted.size()>(sequence2_non_sorted, 8);
    MatchingPairs::solutionInvoker(sequence3_non_sorted, 100);
    MatchingPairs::solutionInvoker<sequence4_non_sorted.size()>(sequence4_non_sorted, 8);
    MatchingPairs::solutionInvoker<emptyArray.size()>(emptyArray, 8);

   /**
    * Process data in chunks
    * If we can do it in parallel:
    * - multiple computers
    * - each one processes each chunk of input
    * - each one produces a set of elements that has seen
    * - we need to merge them
    * - meanwhile the merge is ordered it should be fine?
    *  
   */

    // Bonus: consider having several computers, adapt algorithm to support paralelism
}

}