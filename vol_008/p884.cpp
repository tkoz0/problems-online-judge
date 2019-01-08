#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    uint32_t *sieve = (uint32_t*)calloc(1000001,sizeof(uint32_t));
    // count length of prime factorization for all numbers
    for (uint32_t i = 2, *p = sieve+2; i <= 1000000; ++i, ++p)
    {
        if (*p) continue; // not prime
        for (uint32_t j = i; j <= 1000000; j += i) ++sieve[j]; // multiples
        if (i <= 1000) // exponents
        {
            uint32_t m = i;
            while (m *= i, m <= 1000000)
                for (uint32_t j = m; j <= 1000000; j += m) ++sieve[j];
        }
    }
    // now convert sieve into a cumulative sum
    for (uint32_t *p1 = sieve+1, *p2 = sieve+2; p2 <= sieve+1000000;
        ++p1, ++p2) *p2 += *p1;
    uint32_t n; // process input
    while (scanf("%u",&n) == 1)
    {
        assert(2 <= n and n <= 1000000);
        printf("%u\n",sieve[n]);
    }
    return 0;
}
