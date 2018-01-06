#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <algorithm>
#include <iomanip>

typedef uint32_t u32;
#define MAX_N 100000

u32 gcd(u32 x, u32 y) // euclid algorithm from wikipedia
{
    if (y > x) std::swap(x, y);
    while (y)
    {
        u32 t = y;
        y = x % y;
        x = t;
    }
    return x;
}

int main(int argc, char **argv)
{
    u32 step, mod;
    while (scanf("%u %u\n", &step, &mod) == 2)
    {
        // problem specifies these limits but fails on submission
//        assert(step and step <= MAX_N);
//        assert(mod and mod <= MAX_N);
        std::cout << std::setw(10) << std::right << step;
        std::cout << std::setw(10) << std::right << mod;
        // good sequence must have gcd(step,mod)=1 in order for each possible
        // value to be generated
        if (gcd(step, mod) == 1)
            std::cout << "    Good Choice";
        else std::cout << "    Bad Choice";
        std::cout << std::endl << std::endl;
    }
    return 0;
}
