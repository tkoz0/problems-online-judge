#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
typedef uint32_t u32;
#include <vector>
#include <algorithm>
#define MOST 2000000

int main(int argc, char **argv)
{
    std::vector<u32> nums(MOST,0);
    u32 n, z;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        assert(n <= MOST);
        auto itr = nums.begin();
        while (n--)
        {
            int r = scanf("%u",&z);
            assert(r == 1);
            *(itr++) = z;
        }
        auto itr2 = nums.begin();
        std::sort(itr2,itr);
        printf("%u",*itr2);
        ++itr2;
        while (itr2 != itr)
        {
            printf(" %u",*itr2);
            ++itr2;
        }
        printf("\n");
    }
    return 0;
}
