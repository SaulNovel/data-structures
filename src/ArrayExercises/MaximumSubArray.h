#include <vector>

using std::vector;

namespace MaximumSubArray
{

/**
 * Implementation of Kadane's algorithm for Maximum subarray problem: Time complexity O(n)
 * - local_maximum[i] = max(A[i], A[i] + local_maximum(i-1))
 *
*/
class Solution1 {

private:

    struct MaxSubArray{
        int sum;
        int start;
        int end;

        bool operator>(const MaxSubArray& entry) {
            return (this->sum > entry.sum) ? true : false;
        }
    };

    /**
    * Updates MaxSubArray entry if currentNum greater than (currentNum + entry.sum)
    * 
    * @param entry structure of type MaxSubArray
    * @param num
    * @param index position within an array
    */ 
    void updateMaxSubArray(MaxSubArray& entry,  int num, int index) {
        int combination = num + entry.sum;
        if(num > combination) {
            entry = {num, index, index};
            return;
        }

        entry.sum = combination;
        entry.end = index;
    }

public:
    int maxSubArray(vector<int>& nums) {
        
        MaxSubArray globalMax;
        MaxSubArray localMax;

        if (nums.empty()) {
            return 0;
        }

        int length = static_cast<int>(nums.size());
        if (length == 1) {
            return nums.at(0);
        }

        globalMax = {nums[0], 0, 0};
        localMax = globalMax;

        for (int i=1; i<length; i++) {
            // Local maximum -> max (A[i], A[i] + localMax(i-1))
            updateMaxSubArray(localMax, nums[i], i);

            // Update global maximum if applicable
            globalMax = (localMax > globalMax) ? localMax : globalMax;
        }

        return globalMax.sum;
    }
};



/**
 * Given an integer array nums, find the contiguous subarray 
 * (containing at least one number) which has the largest 
 * sum and return its sum.
 * 
 * A subarray is a contiguous part of an array.
 * 
 * Example:
 * - Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * - Output: 6
 * - Explanation: [4,-1,2,1] has the largest sum = 6.
 * 
 * Example 2:
 * - Input: nums = [1]
 * - Output: 1
 * 
 * Example 3:
 * - Input: nums = [5,4,-1,7,8]
 * - Output: 23
 * 
 * Constraints:
 * - (1 <= nums.length <= 3 * 104)
 * - (-105 <= nums[i] <= 105)
 * 
 * Follow up: If you have figured out the O(n) solution, try coding 
 * another solution using the divide and conquer approach, which is more subtle.
 *
 */
void test() {

    Solution1 testSolution1;
    vector<int> vec1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "maximum: " << testSolution1.maxSubArray(vec1) << std::endl;

    vector<int> vec2 = {-2, 1, -3, 4, -1, 2};
    std::cout << "maximum: " << testSolution1.maxSubArray(vec2) << std::endl;

    vector<int> vec3 = {1};
    std::cout << "maximum: " << testSolution1.maxSubArray(vec3) << std::endl;

    vector<int> vec4 = {5, 4, -1, 7, 8};
    std::cout << "maximum: " << testSolution1.maxSubArray(vec4) << std::endl;

}

}