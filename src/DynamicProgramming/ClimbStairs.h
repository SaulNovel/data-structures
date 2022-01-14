#include <iostream>

namespace ClimbStairs
{

/**
 * Climbing Stairs
 *  
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Example 1:
 * - Input: n = 2
 * - Output: 2
 * - Explanation: There are two ways to climb to the top.
 * - 1. 1 step + 1 step
 * - 2. 2 steps
 * 
 * Example 2:
 * - Input: n = 3
 * - Output: 3
 * - Explanation: There are three ways to climb to the top.
 * - 1. 1 step + 1 step + 1 step
 * - 2. 1 step + 2 steps
 * - 3. 2 steps + 1 step
 * 
 * Constraints:
 * - 1 <= n <= 45
 * 
*/

// The total distinct ways to climb to i th stair is actually 
// the sum of the distinct ways of i – 2 and i – 1 stairs.
class Solution {
public:
    int climbStairs(int n) {
        if (n == 0) { return 0; }
        
        if (n == 1) { return 1; }

        prevWays_ = {1, 1};
        total_ = 0;

        for (int i=2; i<=n; i++) {
            total_ = prevWays_.first + prevWays_.second;

            prevWays_.first = prevWays_.second;
            prevWays_.second = total_;
        }

        return total_;
    }

private:
    std::pair<int, int> prevWays_;
    int total_;

};

}