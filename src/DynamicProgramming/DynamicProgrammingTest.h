#include <iostream>
#include <string>
#include <chrono>

#include <DynamicProgramming/Memoization.h>

#include <DynamicProgramming/BottomUp.h>

#include <DynamicProgramming/HouseRobber.h>

#include <DynamicProgramming/BuySellStock.h>

#include <DynamicProgramming/ClimbStairs.h>

class ScopeTimer {
public:
    ScopeTimer(const std::string& testCase):
        start_(std::chrono::high_resolution_clock::now()),
        testCase_(testCase)
    {}

    ~ScopeTimer() {
        const auto durationRaw = std::chrono::high_resolution_clock::now() - start_;
        double durationMs = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(durationRaw).count())/1e3;
        const std::string message = testCase_ + " -> " + std::to_string(durationMs) + " ms";

        std::cout << message << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
    const std::string testCase_;
};


void memoization_test() {

    Memoization::Memoization memoization;

    {
    ScopeTimer scopeTimer("- First call to calculateFibonacci");
    std::cout << "result: " << memoization.calculateFibonacci(29) << std::endl;
    }

    {
    ScopeTimer scopeTimer("- Second call to calculateFibonacci");
    std::cout << "result: " << memoization.calculateFibonacci(29) << std::endl;
    }
}

void memoization2_test() {

    Memoization::Memoization memoization;
    {
    ScopeTimer scopeTimer("- calculateFibonacci");
    std::cout << "Fibonacci of 29: " << memoization.calculateFibonacci(29) << std::endl;
    }
    {
    ScopeTimer scopeTimer("- calculateFibonacci");
    std::cout << "Fibonacci of 30: " << memoization.calculateFibonacci(30) << std::endl;
    }

    Memoization::Memoization memoization2;
    {
    ScopeTimer scopeTimer("- calculateFibonacci2");
    std::cout << "Fibonacci of 29: " << memoization2.calculateFibonacci2(29) << std::endl;
    }
    {
    ScopeTimer scopeTimer("- calculateFibonacci2");
    std::cout << "Fibonacci of 30: " << memoization2.calculateFibonacci2(30) << std::endl;
    }

}

void bottomUp_test() {
    BottomUp::BottomUp bottomUp;
    std::cout << "Fibonacci of 30: " << bottomUp.calculateFibonacci(30) << std::endl;
}

void buySellStock_test() {

    const std::vector<int> stock1 = {7, 1, 5, 3, 6, 4};
    const std::vector<int> stock2 = {7, 6, 4, 3, 1};

    BuySellStock::Solution sol;
    std::cout << "Profit for stock1: " << sol.maxProfit(stock1) << std::endl;
    std::cout << "Profit for stock2: " << sol.maxProfit(stock2) << std::endl;
    std::cout << "Profit for stock2: " << sol.maxProfit({1, 2}) << std::endl;
}

void climbStairs_test() {
    ClimbStairs::Solution sol;
    std::cout << "Number of ways to climb 3 stairs: " << sol.climbStairs(3) << std::endl;
    std::cout << "Number of ways to climb 4 stairs: " << sol.climbStairs(4) << std::endl;
    std::cout << "Number of ways to climb 5 stairs: " << sol.climbStairs(5) << std::endl;
}

void houseRobber_test() {

    const std::vector<int> sector1 = {2, 7, 9, 3, 1};
    const std::vector<int> sector2 = {1, 2, 3, 1};
    const std::vector<int> sector3 = {2, 1, 1, 2};
    const std::vector<int> sector4 = {1, 3, 1};

    HouseRobber::Solution sol;
    std::cout << "Solution: " << std::endl;
    std::cout << "- Profit for sector1: " << sol.rob(sector1) << std::endl;
    std::cout << "- Profit for sector2: " << sol.rob(sector2) << std::endl;
    std::cout << "- Profit for sector3: " << sol.rob(sector3) << std::endl;
    std::cout << "- Profit for sector4: " << sol.rob(sector4) << std::endl;

    HouseRobber::Solution_Optimized solOptimized;
    std::cout << "Solution Optimized: " << std::endl;
    std::cout << "- Profit for sector1: " << solOptimized.rob(sector1) << std::endl;
    std::cout << "- Profit for sector2: " << solOptimized.rob(sector2) << std::endl;
    std::cout << "- Profit for sector3: " << solOptimized.rob(sector3) << std::endl;
    std::cout << "- Profit for sector4: " << solOptimized.rob(sector4) << std::endl;
}

/**
 * Dynamic programming -> way to improve your algorithm by storing intermediate results
 * 
 * Dynamic programming: Divide & conquer + Memoization
 * Steps to see if we can use dynamic programming for a problem:
 * 1) Can be divided into subproblems
 * 2) Recursive solution
 * 3) Are there repetitive subproblems?
 * 4) Mmeoize subproblems 
*/ 
namespace DynamicProgrammingTest
{

void test() {
    //memoization_test();
    memoization2_test();

    bottomUp_test();

    //buySellStock_test();

    //climbStairs_test();

    //houseRobber_test();
}

}