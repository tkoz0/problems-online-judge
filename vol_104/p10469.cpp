#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
typedef uint32_t u32;

int main(int argc, char **argv)
{
    u32 a, b;
    while (scanf("%u %u",&a,&b) == 2) printf("%u\n",a^b);
    return 0;
}
