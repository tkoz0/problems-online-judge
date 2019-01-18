#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

uint32_t counts[101];

void zero_counts() // reset count of each age
{
    for (uint32_t i = 0; i <= 100; ++i) counts[i] = 0;
}

int main(int argc, char **argv)
{
    uint32_t n, x, a;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        assert(n < 2000000);
        zero_counts();
        while (n--) // process input
        {
            scanf("%u",&x);
            ++counts[x];
        }
        a = 0;
        while (!counts[a]) ++a; // find minimum age in list
        --counts[a];
        printf("%u",a); // print first
        while (a <= 100)
        {
            while (counts[a]--) printf(" %u",a);
            ++a;
        }
        printf("\n");
    }
    return 0;
}
