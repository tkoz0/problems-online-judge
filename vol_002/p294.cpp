#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t u32;
#define MAXU 1000000000
#define MAXDIF 10000

// count divisors with formula based on factorization
u32 divisors(u32 n)
{
    if (!n) return 0;
    u32 count = 0;
    while (n % 2 == 0) count += 1, n >>= 1;
    u32 total = count+1;
    u32 d = 3; // odd divisors
    while (d*d <= n)
    {
        count = 0;
        while (n % d == 0) count += 1, n /= d;
        total *= count+1;
        d += 2;
    }
    if (n != 1) total <<= 1; // last prime factor, multiply by 2
    return total;
}

int main(int argc, char **argv)
{
    u32 N;
    scanf("%u\n",&N); // number of test cases
    while (N--)
    {
        u32 L, U;
        int r = scanf("%u %u\n",&L,&U);
        assert(r == 2); // checks on input
        assert(L and L <= U and U <= MAXU);
        assert(U - L <= MAXDIF);
        u32 D = 0, P; // max divisors, number with most divisors
        for (u32 i = L; i <= U; ++i)
        {
            u32 divs = divisors(i);
            if (divs > D) D = divs, P = i;
        }
        printf("Between %u and %u, %u has a maximum of %u divisors.\n",L,U,P,D);
    }
    return 0;
}
