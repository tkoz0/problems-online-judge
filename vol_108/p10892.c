#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint32_t u32;

u32 divisors(u32 N)
{
    assert(N);
    u32 divs=1,d,dc;
    while (N % 2 == 0) // 1 + exponent of 2
        ++divs, N /= 2;
    for (d = 3; d * d <= N; d += 2)
    {
        if (N % d) continue; // not divisible
        dc = 2, N /= d; // count exponent
        while (N % d == 0) // remaining divisors
            ++dc, N /= d;
        divs *= dc;
    }
    if (N != 1) divs *= 2; // last prime factor
    return divs;
}

u32 divs[32]; // will be enough space for this problem
u32 mults[32]; // corresponing multiplicity

void populate_divs(u32 N)
{
    assert(N);
    u32 d,i=0,m;
    if (N % 2 == 0) divs[i] = 2, N /= 2, m = 1;
    while (N % 2 == 0) N /= 2, ++m;
    mults[i++] = m;
    for (d = 3; d * d <= N; d += 2)
    {
        if (N % d) continue;
        divs[i] = d, N /= d, m = 1;
        while (N % d == 0) N /= d, ++m;
        mults[i++] = m;
    }
    if (N != 1) divs[i] = N, mults[i++] = 1;
    divs[i] = 0, mults[i] = 0; // terminate
}

u32 lcm_cardinality(u32 N)
{
    assert(N);
    populate_divs(N);
    u32 d1,d2,cardinality=0,xcount1,xcount2,di,m1,m2,d1c,d2c;
    for (d1 = 1; d1 * d1 < N; ++d1)
    {
        if (N % d1) continue;
        d2 = N / d1; // divisor pair d1*d2=N
        // given a divisor, the other number x (in lcm(d,x)) must:
        // given a prime divisor of N (p):
        // if d captures the full multiplicity of p, x can have any power of p
        // if not, then x must have the full multiplicity of p
        xcount1 = 1, xcount2 = 1;
        for (di = 0; divs[di]; ++di) // for each distinct prime factor of N
        {
            m1 = 0, m2 = 0; // count multiplicities in d1 and d2
            d1c = d1, d2c = d2;
            while (d1c % divs[di] == 0) d1c /= divs[di], ++m1;
            while (d2c % divs[di] == 0) d2c /= divs[di], ++m2;
            // when d1,d2 capture full multiplicity of divs[di]
            if (m1 == mults[di]) xcount1 *= mults[di]+1;
            if (m2 == mults[di]) xcount2 *= mults[di]+1;
        }
        cardinality += xcount1 + xcount2;
    }
    cardinality += 1; // (N,N) pair is not counted twice
    cardinality /= 2; // counts each pair twice (except possibly next one)
    if (d1 * d1 == N) // perfect square
        cardinality += 1; // sqrt cant capture full multiplicity of any prime
    return cardinality;
}

int main(int argc, char **argv)
{
    u32 N,C;
    for (;;)
    {
        int r = scanf("%u",&N);
        assert(r == 1);
        if (!N) break;
        C = lcm_cardinality(N);
        printf("%u %u\n",N,C);
    }
    return 0;
}
