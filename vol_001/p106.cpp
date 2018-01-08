#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;
#define MAX_N 1000000

int main(int argc, char **argv)
{
    u32 N;
    while (scanf("%u\n", &N) == 1)
    {
        assert(N and N <= MAX_N);
        // first result is num coprime triples with all components <= N
        // second result is how many nums <= N are not part of any triple
    }
    return 0;
}
