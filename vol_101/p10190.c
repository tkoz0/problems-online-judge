#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

uint32_t seq[100]; // should be enough memory

int main(int argc, char **argv)
{
    uint32_t n,m;
    while (scanf("%u%u",&n,&m) == 2)
    {
        uint32_t i = 0;
        while (n != 1)
        {
            seq[i++] = n;
            if (n % m != 0) break;
            n /= m;
        }
        if (n == 1)
        {
            for (uint32_t j = 0; j < i; ++j) printf("%u ",seq[j]);
            printf("1\n");
        }
        else printf("Boring!\n");
    }
    return 0;
}
