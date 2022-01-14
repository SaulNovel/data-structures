#include <vector>
#include <iostream>

using std::vector;

namespace RotateArray
{

/**
try the 3 solutions:
- brute force O(n*k)
- copy the array O(n)
- reverse array -> reverse whole array, separate array: k | n-k, reverse k, reverse n-k 
*/ 
class Solution {

private:

    void printRotatedArray(const vector<int>& nums, int k) {
        std::cout << "k = " << k << " -> [";
        for (size_t i=0; i<nums.size(); i++) {
            std::cout << nums[i] << ((i<nums.size()-1) ? ", " : "]");
        }
        std::cout << std::endl;
    }

    /**
    * Rotates array by 1 element (only useful with brute force approach)
    */
    void rotateByOne(vector<int>& nums) {
        int length = static_cast<int>(nums.size());
        int latest = nums[length-1];
        for (int i=(length-1); i>0; i--) {
            nums[i] = nums[i-1];
        }
        nums[0] = latest;
    }

    void reverseArray(int* array, int size) {
        int start = 0;
        int end = size -1;

        while (start < end) {
            std::swap(array[start], array[end]);
            start++;
            end--;
        }

    }


public:

    /**
    * Rotates an array k elements to the right
    * 
    * Brute force approach:
    * - time complexity O(n * k)
    * - space complexity O(1)
    * 
    */
    void rotateByBruteForce(vector<int>& nums, int k) {
        bool noRot = nums.empty() || (nums.size() < 2) || (k <= 0) || (k == static_cast<int>(nums.size()));
        if (noRot) {
            return;
        }

        for (int i=0; i<k; i++) {
            rotateByOne(nums);
        }

        // TODO: debugging
        printRotatedArray(nums, k);

    }

    /**
    * Rotates an array k elements to the right
    * 
    * Copy array approach:
    * - time complexity O(n)
    * - space complexity O(n)
    * 
    */
    void rotateByCopy(vector<int>& nums, int k) {
        bool noRot = nums.empty() || (nums.size() < 2) || (k <= 0) || (k == static_cast<int>(nums.size()));
        if (noRot) {
            return;
        }

        const std::vector<int> numsCopy(nums);
        int length = static_cast<int>(nums.size());

        for (int i=0; i<length; i++) {
            int rotIdx = (i+k) % length;
            nums[rotIdx] = numsCopy[i];
        }

        // TODO: debugging
        printRotatedArray(nums, k);

    }

    /**
    * Rotates an array k elements to the right
    * 
    * Reverse method approach:
    * - time complexity O(n)
    * - space complexity O(1)
    * 
    */
    void rotateByReverse(vector<int>& nums, int k) {
        
        int size = static_cast<int>(nums.size());
        bool noRot = nums.empty() || (nums.size() < 2) || (k <= 0) || (k == size);
        if (noRot) {
            return;
        }

        int rot = (k < size) ? k : (k % size);

        // reverse whole array
        reverseArray(nums.data(), size);

        // reverse left
        reverseArray(nums.data(), rot);

        // reverse right
        size -= rot;
        reverseArray((nums.data() + rot), size);

        // TODO: debugging
        printRotatedArray(nums, k);
    }

};


// TODO use temp for first jump
// jump from index to index checking which element should go there and do the change

/**
 * Given an array, rotate the array to the right by k steps, where k is non-negative.
 * 
 * Example 1:
 * - Input: nums = [1,2,3,4,5,6,7], k = 3
 * - Output: [5,6,7,1,2,3,4]
 * - Explanation:
 * - rotate 1 steps to the right: [7,1,2,3,4,5,6]
 * - rotate 2 steps to the right: [6,7,1,2,3,4,5]
 * - rotate 3 steps to the right: [5,6,7,1,2,3,4]
 * 
 * Example 2:
 * - Input: nums = [-1,-100,3,99], k = 2
 * - Output: [3,99,-1,-100]
 * - Explanation: 
 * - rotate 1 steps to the right: [99,-1,-100,3]
 * - rotate 2 steps to the right: [3,99,-1,-100]
 * 
 *  Constraints:
 * - 1 <= nums.length <= 10^5
 * - -2^31 <= nums[i] <= 2^31 - 1
 * - 0 <= k <= 10^5
 * 
 * Follow up:
 * - Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
 * - Could you do it in-place with O(1) extra space?
 * 
 */

void test() {
    Solution sol;
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotateByReverse(nums, 3);
    }
    /*
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotate(nums, 2);
    }
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotate(nums, 3);
    }
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotate(nums, 4);
    }
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotate(nums, 5);
    }
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotate(nums, 6);
    }
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
        sol.rotate(nums, 7);
    }

    std::vector<int> nums = {-1, -100, 3, 99};
    sol.rotateByCopy(nums, 2);
    */

}

}