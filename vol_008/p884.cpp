#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    bool *sieve = (bool*)calloc(1000000,1); // sieve primes
    for (uint32_t i = 2; i <= 1000; ++i)
    {
        if (sieve[i]) continue; // composite
        for (uint32_t j = i*i; j <= 1000000; j += i)
            sieve[j] = true;
    }
    std::vector<uint32_t> primes; // make list of primes and their exponents
    for (uint32_t i = 2; i < 1000000; ++i)
    {
        if (!sieve[i])
        {
            primes.push_back(i);
            if (i <= 1000) // include exponents up to 1000
            {
                uint32_t j = i;
                while (j *= i, j <= 1000000)
                    primes.push_back(j);
            }
        }
    }
    std::sort(primes.begin(),primes.end()); // put in order
    uint32_t n;
    while (scanf("%u",&n) == 1) // process factorials
    {
        assert(2 <= n and n <= 1000000);
        uint32_t count = 0;
        for (auto p : primes)
        {
            if (p > n) break; // too large
            count += n / p;
        }
        printf("%u\n",count);
    }
    free(sieve);
    return 0;
}
