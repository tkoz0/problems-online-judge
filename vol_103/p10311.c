#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
typedef uint32_t u32;
#define LIMIT 100000000

bool sieve[LIMIT+1];

void init_sieve()
{
    memset(sieve,1,sizeof(*sieve)*(LIMIT+1)); // intially all prime
    sieve[0] = 0;
    sieve[1] = 0;
    for (u32 p = 2; p * p <= LIMIT; ++p)
    {
        if (!sieve[p]) continue; // composite
        // cross off multiples starting from p*p
        for (u32 q = p*p; q <= LIMIT; q += p)
            sieve[q] = 0;
    }
}

bool prime_sum(u32 n, u32 *p1, u32 *p2)
{
    assert(0 < n && n <= LIMIT);
    if (n < 5) return false; // need 2 distinct primes, 2+2=4 does not work
    if (n % 2)
    {
        if (sieve[n-2]) // must be the sum of even and odd so need 2
        {
            *p1 = 2;
            *p2 = n-2;
            return true;
        }
        else return false;
    }
    else
    {
        u32 q1 = n/2-1, q2 = n/2+1;
        while (q2 < n)
        {
            if (sieve[q1] && sieve[q2])
            {
                *p1 = q1;
                *p2 = q2;
                return true;
            }
            --q1;
            ++q2;
        }
        return false;
    }
}

int main(int argc, char **argv)
{
    init_sieve();
//printf("sieve done\n");
    u32 n, p1, p2;
    while (scanf("%u",&n) == 1)
    {
        if (prime_sum(n,&p1,&p2))
            printf("%u is the sum of %u and %u.\n",n,p1,p2);
        else printf("%u is not the sum of two primes!\n",n);
    }
    return 0;
}
