#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

typedef int32_t i32;
typedef uint32_t u32;

std::vector<i32> factorize(i32 z)
{
    assert(z > 0);
    // convert to unsigned to solve d*d<=n problem with signed max
    u32 n = (u32)z;
    std::vector<i32> f;
    while (n % 2 == 0)
    {
        f.push_back(2);
        n /= 2;
    }
    u32 d = 3;
    while (d*d <= n)
    {
        while (n % d == 0)
        {
            f.push_back((i32)d);
            n /= d;
        }
        d += 2;
    }
    if (n != 1) f.push_back((i32)n);
    return f;
}

#define SQRTMAX 46341

int main(int argc, char **argv)
{
    // cache strings for numbers up to sqrt(max) for speed
    char **cache = (char**) malloc(sizeof(char*) * SQRTMAX);
    for (i32 i = 0; i < SQRTMAX; ++i)
    {
        cache[i] = (char*) malloc(6);
        sprintf(cache[i],"%i",i);
    }
    i32 g;
    char tmp[11]; // for converting larger integers to strings
    while (scanf("%i",&g) == 1)
    {
        if (!g) break; // 0 terminates input
        assert(g != -1 and g != 1);
        printf("%i = ",g);
        if (g < 0)
        {
            g = -g;
            printf("-1 x ");
        }
        std::vector<i32> f = factorize(g);
        assert(f.size() > 0);
        std::string s; // factorization in single string
        if (f[0] < SQRTMAX) s += std::string(cache[f[0]]);
        else
        {
            sprintf(tmp,"%i",f[0]);
            s += std::string(tmp);
        }
        for (u32 i = 1; i < f.size()-1; ++i)
        {
            s += " x ";
            s += std::string(cache[f[i]]);
        }
        if (f.size() < 2) // already put last (first) number into string
        {
            std::cout << s << std::endl;
            continue;
        }
        if (f.back() < SQRTMAX)
        {
            s += " x ";
            s += std::string(cache[f.back()]);
        }
        else
        {
            sprintf(tmp,"%i",f.back());
            s += " x ";
            s += std::string(tmp);
        }
        std::cout << s << std::endl;
        // with cache, printing each number separately
//        if (f[0] < SQRTMAX) printf("%s",cache[f[0]]); // first factor
//       else printf("%i",f[0]);
//        // all but last factor are guaranteed in cache range
//        for (u32 i = 1; i < f.size()-1; ++i) printf(" x %s",cache[f[i]]);
//        if (f.size() < 2) // already printed last number (only one)
//        {
//            printf("\n");
//            continue;
//        }
//        if (f.back() < SQRTMAX) printf(" x %s\n",cache[f.back()]);
//        else printf(" x %i\n",f.back());
        // without cache
//        printf("%i",f[0]);
//        for (u32 i = 1; i < f.size(); ++i) printf(" x %i",f[i]);
//        printf("\n");
    }
    return 0;
}
