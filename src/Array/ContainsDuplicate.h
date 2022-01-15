#include <vector>
#include <iostream>
#include <unordered_set>

using std::vector;

namespace ContainsDuplicate
{

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        if (nums.empty() || nums.size() == 1) {
            return false;
        }

        std::unordered_set<int> numsCopy;
        for (int num : nums) {
            if (numsCopy.count(num)) {
                return true;
            }

            numsCopy.emplace(num);
        }

        return false;
        
    }
};

/**
 * Given an integer array nums, return true if any value appears 
 * at least twice in the array, and return false if every element is distinct.
 * 
 * Example 1:
 * - Input: nums = [1,2,3,1]
 * - Output: true
 * 
 * Example 2:
 * - Input: nums = [1,2,3,4]
 * - Output: false
 * 
 * Example 3:
 * - Input: nums = [1,1,1,3,3,4,3,2,4,2]
 * - Output: true
 * 
 *  Constraints:
 * - 1 <= nums.length <= 105
 * - -109 <= nums[i] <= 109 
 * 
 */
void test() {

    Solution sol;

    std::vector<int> nums = {1,2,3,1};
    std::cout << "output: " << sol.containsDuplicate(nums) << std::endl;

    std::vector<int> nums2 = {1,2,3,4};
    std::cout << "output: " << sol.containsDuplicate(nums2) << std::endl;

    std::vector<int> nums3 = {1,1,1,3,3,4,3,2,4,2};
    std::cout << "output: " << sol.containsDuplicate(nums3) << std::endl;
}

}