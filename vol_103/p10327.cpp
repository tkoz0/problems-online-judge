#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
typedef uint32_t u32;

int main(int argc, char **argv)
{
    u32 N;
    while (scanf("%u",&N) == 1)
    {
        u32 x, swaps = 0;
        std::vector<u32> arr;
        while (N--)
        {
            int r = scanf("%u",&x);
            assert(r == 1);
            arr.push_back(x);
        }
        // count inversions with insertion sort
        for (u32 i = 1; i < arr.size(); ++i)
        {
            u32 j = i;
            while (j and arr[j-1] > arr[j])
            {
                std::swap(arr[j-1],arr[j]);
                swaps += 1;
                --j;
            }
        }
        printf("Minimum exchange operations : %u\n",swaps);
    }
    return 0;
}
