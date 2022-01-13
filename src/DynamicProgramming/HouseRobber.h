#include <iostream>

#include <vector>

namespace HouseRobber
{


/**
 * You are a professional robber planning to rob houses along a street.
 * Each house has a certain amount of money stashed, the only constraint 
 * stopping you from robbing each of them is that adjacent houses have security 
 * systems connected and it will automatically contact the police if two 
 * adjacent houses were broken into on the same night.
 * 
 * Given an integer array nums representing the amount of money of each house, 
 * return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Example 1:
 * - Input: nums = [1,2,3,1]
 * - Output: 4
 * - Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 * - Total amount you can rob = 1 + 3 = 4.
 * 
 * Example 2:
 * - Input: nums = [2,7,9,3,1]
 * - Output: 12
 * - Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 * - Total amount you can rob = 2 + 9 + 1 = 12.
 * 
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 0 <= nums[i] <= 400
 * 
*/
class Solution_Optimized {
public:
    int rob(const std::vector<int>& nums) {
        if (nums.empty()) { return 0; }
        
        // Template for dynamic programing
        // - always set to the size of the input + 1
        // - array of the maximum values
        // This implements the bottom up approach
        std::vector<int> dp(nums.size() + 1);
        // no houses -> max is 0
        dp[0] = 0;
        // 1 house -> max is the profit from first house
        dp[1] = nums[0];

        // we already checked the first element, loop starts on 1 (part of the template for dynamic programming)
        for (int i=1; i< static_cast<int>(nums.size()); i++) {
            // each house we look at we calculate a new max
            // this is the only non standar part for dynamic programming problems
            dp[i+1] = getMax(dp[i], (dp[i-1] + nums[i]));
        }

        return dp[dp.size()-1];
    }
private:
    const int getMax(int val1, int val2) const {
        return (val1 > val2) ? val1 : val2;
    }

};

class Solution {
public:

    int rob(const std::vector<int>& nums) {

        if (nums.empty()) { return 0; }

        int size = static_cast<int>(nums.size());
        std::vector<int> profits(nums);
        max_ = -1;
        
        if (size < 3) { return getMax(profits); }

        for (int i=0; i<size; i++) {
            int start = i + 2;
            for (int j=start; j<size; j++) {
                
                int currentProfit = profits[i] + nums[j];
                profits[j] = (currentProfit > profits[j]) ? currentProfit : profits[j];
            }
        }

        return getMax(profits);
    }

private:
    int max_;

    int getMax(const std::vector<int>& profits) {
        for (const int profit : profits) {
            max_ = (profit > max_) ? profit : max_;
        }

        return max_;
    }

};

}