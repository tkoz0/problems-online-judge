#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef uint32_t u32;

int main(int argc, char **argv)
{
    u32 n[9];
    const char *orders[6] = { "BCG", "BGC", "CBG", "CGB", "GBC", "GCB" };
    u32 moved[6];

    // read input: BGC BGC BGC (order for 3 bins)
    while (scanf("%u %u %u %u %u %u %u %u %u",
            n,n+1,n+2,n+3,n+4,n+5,n+6,n+7,n+8) == 9)
    {
        // first 3 are brown,green,clear for bin 1, etc for bins 2 and 3
        // compute how many are moved for all 6 possibilities
        moved[0] = n[3] + n[6] + n[2] + n[8] + n[1] + n[4];
        moved[1] = n[3] + n[6] + n[1] + n[7] + n[2] + n[5];
        moved[2] = n[5] + n[8] + n[0] + n[6] + n[1] + n[4];
        moved[3] = n[5] + n[8] + n[1] + n[7] + n[0] + n[3];
        moved[4] = n[4] + n[7] + n[0] + n[6] + n[2] + n[5];
        moved[5] = n[4] + n[7] + n[2] + n[8] + n[0] + n[3];
        // find min in move counts
        u32 i = 0;
        if (moved[1] < moved[i]) i = 1;
        if (moved[2] < moved[i]) i = 2;
        if (moved[3] < moved[i]) i = 3;
        if (moved[4] < moved[i]) i = 4;
        if (moved[5] < moved[i]) i = 5;
        // output
        printf("%s %u\n", orders[i], moved[i]);
    }
}
