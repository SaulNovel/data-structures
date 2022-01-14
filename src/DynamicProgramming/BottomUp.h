#include <iostream>

// For non-technical interviews:
// https://coggle.it/diagram/W5u8QkZs6r4sZM3J/t/master-the-interview

namespace BottomUp
{

class BottomUp {

public:
    int calculateFibonacci(int x) {
        
        std::vector<int> dp;
        dp.push_back(0);
        dp.push_back(1);

        for (int i=2; i<=x; i++) {
            dp.push_back(dp[i-2] + dp[i-1]);
        }

        return dp[dp.size()-1];
    }
};

}