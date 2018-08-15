#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#define LOWER 10000L
#define UPPER 6227020800L
typedef uint32_t u32;
typedef uint64_t u64;

int main(int argc, char **argv)
{
    u64 n;
    while (scanf("%lu",&n) == 1)
    {
        u64 f = 1;
        for (u64 i = 1; i <= n; ++i)
        {
            f *= i;
            if (!f) break;
        }
        if (f < LOWER) printf("Underflow!\n");
        else if (f > UPPER) printf("Overflow!\n");
        else printf("%lu\n",f);
    }
    return 0;
}
