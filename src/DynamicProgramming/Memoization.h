#include <Recursion/Fibonacci.h>
#include <unordered_map>

namespace Memoization
{
using Fibonacci::Fibonacci;

class Memoization {

public:
    int calculateFibonacci(int x) {
        const auto found = results_.find(x);
        if (found != results_.end()) {
            return found->second;
        }

        Fibonacci fibonacci;
        int result = fibonacci.get(x);
        results_[x] = result;

        return result;
    }

    /**
     * Time complexity O(n)
     * Space complexity O(n)
    */ 
    int calculateFibonacci2(int x) {
        const auto found = results_.find(x);
        if (found != results_.end()) {
            return found->second;
        }

        return fibonacci(x);
    }

private:
    std::unordered_map<int, int> results_;

    int getSequence(int x) {
        const auto found = results_.find(x);
        if (found != results_.end()) {
            return found->second;
        }

        int result = fibonacci(x);
        results_[x] = result;

        return result;
    }

    int fibonacci(int x) {
        if (x < 2) { return x; }

        int second = getSequence(x-1);
        int third = getSequence(x-2);

        return second + third;
    }

};

}