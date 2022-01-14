#include <iostream>

namespace Factorial
{
class FactorialRecursive
{
public:
    int factorial(int x) {
        if (x <=1 ) {
            return 1;
        }

        return x * factorial(x-1);
    }
};

class FactorialIterative
{
public:
    int factorial(int x) {
        int accumulator = 1;
        while(x>1) {
            accumulator = accumulator * x--;
        }

        return accumulator;

    }
};

}