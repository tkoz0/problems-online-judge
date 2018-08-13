#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
typedef uint32_t u32;
typedef int32_t i32;

int main(int argc, char **argv)
{
    u32 N;
    while (scanf("%u",&N) == 1)
    {
        if (!N) break;
        assert(N <= 10000);
        i32 max = 0, current = 0, n;
        while (N--)
        {
            int r = scanf("%i",&n);
            assert(r == 1);
            current += n;
            if (current < 0) current = 0;
            else max = std::max(max,current);
        }
        if (max > 0) printf("The maximum winning streak is %i.\n",max);
        else printf("Losing streak.\n");
    }
    return 0;
}
