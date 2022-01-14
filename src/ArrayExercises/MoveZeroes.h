#include <vector>
#include <iostream>

using std::vector;

namespace MoveZeroes
{


/**
 * [0,1,0,3,12]
 * start from beginning and compare
 * Keep 2 indexes: start/end
 * isZero = arr[i] == 0
 * isNextZero = arr[i+1] == 0
 * 
 * Update for start index: 
 * - First 0 is found 
 * - switching elements
 * 
 * For iteration i
 * 1) isZero ? 
 *    - Yes -> end = i && continue
 *    - No -> switch(arr[start], arr[i])
 * 
 * - Example1 [0, 0, 0, 7] -> [7, 0, 0, 0]
 *   sequence: start=0 end=0; end=1; end=2; switch(arr[start], arr[i]) && start=1
 *
 * - Example2 [0, 0, 0, 7, 3] -> [7, 3, 0, 0, 0]
 *   sequence: start=0 end=0; end=1; end=2; switch(arr[start], arr[i]) && start=1; switch(arr[start], arr[i]) && start=2
 * 
  * - Example2 [0, 0, 7, 3, 0] -> [7, 3, 0, 0, 0]
 *   sequence: start=0 end=0; end=1; switch(arr[start], arr[i]) && start=1 end=2 ; switch(arr[start], arr[i]) && start=2 && end=3; end=4
 */ 
class Solution {

public:
    void moveZeroes(vector<int>& nums) {
        if(nums.empty() || nums.size() == 1) {
            return;
        }

        int length = static_cast<int>(nums.size());
        int start = -1;
        int end = -1;

        for (int i=0; i<length; i++) {
            
            if (nums[i] == 0) {
                // First update for start
                start = (start == -1) ? i : start;
                end = i;
                continue;
            }

            bool zerosFound = (start != -1) && (end != -1);
            if (zerosFound) {
                
                int temp = nums[i];
                nums[i] = nums[start]; // nums[start] = 0
                nums[start] = temp;
                start++;
                end++;
            }
        }

        // TODO: debugging
        std::cout << "output: [";
        for (size_t i=0; i<nums.size(); i++) {
        std::cout << nums[i] << ((i<nums.size()-1) ? ", " : "]");
        }
        std::cout << std::endl;
    }
};

/**
 * Given an integer array nums, move all 0's to the end of it 
 * while maintaining the relative order of the non-zero elements.
 * 
 * Note that you must do this in-place without making a copy of the array.
 * 
 * Example:
 * - Input: nums = [0,1,0,3,12]
 * - Output: [1,3,12,0,0]
 * 
 * Example 2:
 * - Input: nums = [0]
 * - Output: [0]
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -2^31 <= nums[i] <= 2^31 - 1
 * 
 * Follow up: Follow up: Could you minimize the total number of operations done?
 *
 */
void test() {

    Solution sol;
    std::vector<int> nums = {0,1,0,3,12};
    sol.moveZeroes(nums);


}

}