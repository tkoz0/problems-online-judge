#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef uint32_t u32;

int main(int argc, char **argv)
{
    // compute R = B^P mod M
    // 0 <= B,P <= 2^31 - 1 and 1 <= M <= 46340 and 46340^2 < 2^31
    // with these limits, the entire problem is solvable with 32 bit integers
    u32 B, P, M;
    while (scanf("%u\n%u\n%u\n\n", &B, &P, &M) == 3)
    {
        assert(M < (1 << 16)); // prevent overflow
        // using right to left binary modular exponentiation
        // determine modulo of powers of 2 and multiply them and take mod
        u32 R = 1;
        B %= M; // R and B will always be < M and M < 2^16 so now overflow
        while (P)
        {
            if (P & 1) // this bit is set
                R = (R * B) % M;
            P >>= 1; // shift to next bit
            B = (B * B) % M; // square to get to next power of 2
        }
        printf("%u\n", R);
    }
    return 0;
}
