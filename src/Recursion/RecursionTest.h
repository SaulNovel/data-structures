#include <Recursion/Factorial.h>
#include <Recursion/Fibonacci.h>
#include <Recursion/ReverseStringR.h>

namespace RecursionTest {

/**
 * When to use recursion:
 * - Everytime you are using a tree or converting something into a tree, consider recursion
 *   1) Divided into a number of subproblems that are smaller instances of the same problem
 *   2) Each instance of the subproblem is identical in nature
 *   3) The solutions of each subproblem can be combined to solve the problem at hand
 * - Divide and conquer using recursion  
*/ 

using Factorial::FactorialRecursive;
using Factorial::FactorialIterative;
using Fibonacci::Fibonacci;
using ReverseStringR::ReverseString;

void factorial_test() {

    int num = 5;

    FactorialRecursive factorialRecursive;
    std::cout << "Factorial of '" << num << "' using recursion: " << factorialRecursive.factorial(num) << std::endl;

    FactorialIterative factorialIterative;
    std::cout << "Factorial of '" << num << "' using iterations: " << factorialIterative.factorial(num) << std::endl;

}

void fibonacci_test() {
    Fibonacci fibonacci;
    int num = 12;
    std::cout << "Fibonacci of '" << num << "': " << fibonacci.get(num) << std::endl;
}

void reverseString_test() {
    ReverseString reverseStr;
    const std::string str = "HELLO";
    std::cout << str << " -> " << reverseStr.reverse(str) << std::endl; 
    std::cout << str << " -> " << reverseStr.reverse2(str) << std::endl; 
}


void test() {
    //factorial_test();
    //fibonacci_test();
    reverseString_test();
}

}