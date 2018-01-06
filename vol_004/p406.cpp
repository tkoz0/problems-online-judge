#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <algorithm>

typedef uint32_t u32;
#define MAX_N 1000
#define _DEBUG_LIM (MAX_N / 10)

void _debug_prsieve(bool *sieve, u32 N)
{
    for (u32 i = 0; i <= _DEBUG_LIM; ++i)
        printf("%04u: %i\n", i, (int) (!sieve[i]));
}

void gen_sieve(bool *sieve, u32 N)
{
    // false means prime and true means composite
    // 1 is an exception because it is included in this problem
    for (u32 d = 2; d <= (u32) sqrt((double) N); ++d)
    {
        if (sieve[d]) continue; // skip composites
        for (u32 i = d << 1; i <= N; i += d)
            sieve[i] = true; // mark multiples as composite
    }
//    _debug_prsieve(sieve, N);
}

int main(int argc, char **argv)
{
    u32 N, C;
    bool *sieve = (bool*) calloc((MAX_N + 1), sizeof(bool));
    gen_sieve(sieve, MAX_N);
    while (scanf("%u %u\n", &N, &C) == 2)
    {
        assert(N and N <= MAX_N); // 1 <= N <= 1000
        assert(C and C <= N); // 1 <= C <= N
        // find middle prime(s)
        bool *beg = &(sieve[1]), *end = &(sieve[N]);
        while (*end) --end; // find prime
        assert((not *beg) and (not *end)); // both must point to primes
        while (end > beg) // move inwards to find middle
        {
            ++beg, --end; // move, then find next primes
            while (*beg) ++beg;
            while (*end) --end;
        }
        // beg == end if odd num of primes, beg=end+1 if even number of primes
        assert(end <= beg); // meet at middle of pass each other
        std::swap(end, beg);
        assert(beg <= end);
        for (u32 c = 1; c != C; ++c) // 2C or 2C-1 numbers
        {
            if (beg == &(sieve[1])) break; // stop when reaching max bounds
            // move outward
            --beg, ++end;
            while (*beg) --beg;
            while (*end) ++end;
        }
        // write output between and including beg and end pointers
        printf("%u %u:", N, C);
        for (++end; beg != end; ++beg)
            if (not *beg) // prime
                printf(" %lu", beg - sieve);
        printf("\n\n");
    }
    free(sieve);
    return 0;
}
