#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
typedef uint32_t u32;
#define MAXIMUM 1000000
static_assert(MAXIMUM < (1u<<31),"");

u32 factors[1+MAXIMUM];

int main(int argc, char **argv)
{
    // generate sieve
    for (u32 i = 0; i <= MAXIMUM; ++i) factors[i] = 0; // zero
    for (u32 f = 2; f <= MAXIMUM; ++f)
    {
        if (factors[f]) continue; // not prime
        for (u32 i = f; i <= MAXIMUM; i += f) ++factors[i];
    }
    u32 n;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        assert(n <= MAXIMUM);
        printf("%u : %u\n",n,factors[n]);
    }
    return 0;
}
