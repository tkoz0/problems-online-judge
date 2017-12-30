#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <vector>
#include <algorithm>

typedef uint32_t u32;
#define UGLY_INDEX 1500

u32 compute1(u32 ugly_index)
{
    typedef uint32_t nt; // number type for calculations
    nt limit = 2;
    std::vector<nt> nums;
    nums.reserve(ugly_index);
    nums.push_back(1);
    nt i = 1, j = 1, k = 1; // exponents of 5,3,2 respectively
    while (nums.size() < ugly_index)
    {
        assert(limit);
        limit <<= 1; // double limit
        while (i < limit)
        {
            nt ij;
            while ((ij = i * j) < limit)
            {
                nt val = ij;
                // multiply by 2 (last factor) until exceeding limit
                while (val < limit)
                {
                    if (val >= (limit >> 1))
                        nums.push_back(val);
                    val <<= 1;
                }
                j *= 3;
                k = 1; // reset
            }
            i *= 5;
            j = 1; // reset
        }
        i = 1; // reset
    }
    std::sort(nums.begin(), nums.end());
    return nums[ugly_index - 1];
}

// ugly numbers, 1 included, otherwise only have prime factors 2,3,5
int main(int argc, char **argv)
{
    printf("The 1500'th ugly number is %u.\n", compute1(UGLY_INDEX));
    return 0;
}
