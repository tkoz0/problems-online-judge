#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
typedef uint32_t u32;
#define LIMIT 0x7FFFFFFF
#define MAXDIF 1000000

u32 *primes; // primes for sieving

void gen_small_primes()
{
    u32 S = (u32)sqrt(LIMIT);
    bool *sieve = (bool*)calloc(S+1,sizeof(*sieve)); // false = prime
    sieve[0] = sieve[1] = 1;
    for (u32 d = 2; d*d <= S; ++d)
    {
        if (sieve[d]) continue; // composite
        for (u32 z = d*d; z <= S; z += d)
            sieve[z] = 1;
    }
    u32 count = 0;
    for (u32 z = 2; z <= S; ++z)
        if (!sieve[z]) ++count;
    primes = (u32*)malloc((count+1)*sizeof(*primes));
    u32 i = 0;
    for (u32 z = 2; z <= S; ++z)
        if (!sieve[z]) primes[i++] = z;
    primes[i] = 0; // array termination
    free(sieve);
}

bool LUsieve[MAXDIF+1];

int main(int argc, char **argv)
{
    gen_small_primes();
    u32 L,U;
    while (scanf("%u%u",&L,&U) == 2)
    {
        assert(1 <= L && L < U && U <= LIMIT);
        memset(LUsieve,1,U-L+1); // initially all prime
        if (L == 1) LUsieve[0] = 0; // corner case
        // LUsieve[i] represents L+i
        for (u32 *pptr = primes; *pptr; ++pptr) // prime pointer in primes array
        {
            if (*pptr * *pptr > U) break; // no need to go farther
            u32 low = L; // starting index at next *pptr multiple
            if (low % *pptr) low += *pptr - (low % *pptr);
            if (low < *pptr * *pptr) low = *pptr * *pptr; // start at least here
            for (u32 z = low; z <= U; z += *pptr)
                LUsieve[z-L] = 0; // set composite
        }
        // LUsieve should only have true where primes are
        // p1i,p2i are index of 2 adjacent primes in LUsieve
        // dmin,dmax are the best distances found
        // c1,c2 are closest primes, d1,d2 are farthest
        u32 p1i, p2i, dmin = -1, dmax = 0, c1, c2, d1, d2;
        for (p1i = 0; p1i <= U-L && !LUsieve[p1i]; ++p1i); // find 1st prime
        if (p1i > U-L) // cant find adjacent pair
        {
            printf("There are no adjacent primes.\n");
            continue;
        }
        for (p2i = p1i+1; p2i <= U-L && !LUsieve[p2i]; ++p2i); // find 2nd prime
        if (p2i > U-L) // cant find adjacent
        {
            printf("There are no adjacent primes.\n");
            continue;
        }
        dmin = dmax = p2i-p1i;
        c1 = L+p1i, c2 = L+p2i;
        d1 = L+p1i, d2 = L+p2i;
//printf("p1i,p2i = %u,%u\n",L+p1i,L+p2i);
        for (;;) // search for more
        {
            p1i = p2i++;
            for (; p2i <= U-L && !LUsieve[p2i]; ++p2i); // find next
            if (p2i > U-L) break; // done
//printf("new p2i = %u\n",L+p2i);
            if (p2i-p1i < dmin) // new min
                dmin = p2i-p1i, c1 = L+p1i, c2 = L+p2i;
            if (p2i-p1i > dmax) // new max
                dmax = p2i-p1i, d1 = L+p1i, d2 = L+p2i;
        }
        printf("%u,%u are closest, %u,%u are most distant.\n",c1,c2,d1,d2);
    }
    free(primes);
    return 0;
}
