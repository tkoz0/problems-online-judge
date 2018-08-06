#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
typedef uint32_t u32;

int main(int argc, char **argv)
{
    u32 n;
    char buf[33];
    buf[32] = '\0';
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        u32 z = n, bits = 0;
        for (; z; ++bits) z &= z-1; // brian kernighan algorithm
        // output n in binary
        char *p = buf+32; // start at the null terminator
        while (n)
        {
            *(--p) = n & 1 ? '1' : '0'; // insert binary digits leftward
            n >>= 1;
        }
        printf("The parity of %s is %u (mod 2).\n",p,bits);
    }
    return 0;
}
