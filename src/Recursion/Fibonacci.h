#ifndef __FIBONACCI__   // if x.h hasn't been included yet...
#define __FIBONACCI__   //   #define this so the compiler knows it has been included

#include <iostream>

namespace Fibonacci
{

/**
 * Given a number N return the index value of the Fibonacci sequence,
 * where the sequence is:
 * 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 ...
 * the pattern of the sequence is that each value is the sum of the
 * 2 previous values. that means that for N=5 -> 2+3
*/ 
class Fibonacci
{
public:
    /**
     * O(2^n)  (the iterative approach is much faster O(n))
    */ 
    int get(int x) {
        // trivial cases
        //if (x == 0) { return 0; }
        //if (x == 1) { return 1; }

        if (x < 2) { return x; }

        return get(x-1) + get(x-2);

        // 2 -> get(1) + get(0) = 1 + 0 = 1
        // 3 -> get(2) + get(1) = 1 + 1 = 2
    }
};

}

#endif