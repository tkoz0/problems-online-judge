#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef uint32_t u32;
#define LIMIT 1000000
#define WRONG "Goldbach's conjecture is wrong."

bool* make_sieve() // sieve or erasthenes
{
    bool *s = (bool*) calloc(LIMIT,sizeof(bool));
    s[0] = s[1] = 1;
    u32 sq = (u32)sqrt(LIMIT);
    for (u32 d = 2; d <= sq; ++d)
    {
        if (s[d]) continue; // not prime
        for (u32 i = d*d; i < LIMIT; i += d) s[i] = 1;
    }
    return s;
}

int main(int argc, char **argv)
{
    u32 n;
    bool *sieve = make_sieve(); // false=prime
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        assert(6 <= n and n < LIMIT and n % 2 == 0);
        u32 a = 0, b; // find a+b=n with minimum prime a
        for (u32 aa = 2; aa <= n/2; ++aa)
            if (!sieve[aa] and !sieve[n-aa])
            {
                a = aa, b = n-aa;
                break;
            }
        if (a == 0) // no such pair found (should never happen)
        {
            printf("%s\n",WRONG);
            break;
        }
        printf("%u = %u + %u\n",n,a,b);
    }
    return 0;
}
