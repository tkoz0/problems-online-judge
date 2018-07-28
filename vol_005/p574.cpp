#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

typedef uint32_t u32;

bool recurse(const std::vector<u32>& maxsums, const std::vector<u32>& nums,
        std::vector<u32>& ints, u32 sum, u32 index, u32 target)
{
    if (sum > target) return false;
    if (sum == target) // print result
    {
        printf("%u",ints.front());
        for (u32 i = 1; i < ints.size(); ++i) printf("+%u",ints[i]);
        printf("\n");
        return true;
    }
    bool foundany = false;
    // to avoid duplicates, pick consecutive identical numbers only
    u32 next = index+1;
    if (next < nums.size() and maxsums[next] < target-sum) return false;
    if (next < nums.size() and nums[next] == nums[index])
    {
        ints.push_back(nums[next]);
//for(u32 y=0;y<ints.size();++y)printf("-");printf("%u\n",nums[next]);
        foundany |= recurse(maxsums, nums, ints, sum+nums[next], next, target);
        ints.pop_back(); // backtrack
    }
    // find first of any other number to pick
    while (next < nums.size())
    {
        if (maxsums[next] < target-sum) break;
        if (nums[next] == nums[next-1]) goto increm; // must pick first instance
        ints.push_back(nums[next]);
//for(u32 y=0;y<ints.size();++y)printf("-");printf("%u\n",nums[next]);
        foundany |= recurse(maxsums, nums, ints, sum+nums[next], next, target);
        ints.pop_back(); // backtrack
        increm:
        ++next;
    }
    return foundany;
}

int main(int argc, char **argv)
{
    u32 t, n;
    while (scanf("%u",&t) == 1)
    {
        int r = scanf("%u",&n);
        assert(r == 1);
        if (!n) break;
        assert(1 <= n and n <= 12);
        assert(1 <= t and t <= 1000);
        std::vector<u32> nums;
        while (n--) // read numbers
        {
            u32 z;
            r = scanf("%u",&z);
            assert(r == 1);
            if (nums.size()) assert(z <= nums.back()); // must be sorted
            nums.push_back(z);
        }
        printf("Sums of %u:\n",t);
        bool foundany = false;
        std::vector<u32> stack; // recursion array
        // sum of numbers after an index (for eliminating search subtrees)
        std::vector<u32> maxsum(nums.size());
        maxsum[maxsum.size()-1] = nums[nums.size()-1];
        for (u32 i = maxsum.size()-1; i--;) maxsum[i] = maxsum[i+1] + nums[i];
        stack.push_back(0);
        for (u32 i = 0; i < nums.size(); ++i)
        {
            // only pick 1st instance of each number
            if (i > 0 and nums[i-1] == nums[i]) continue;
            stack[0] = nums[i];
//printf("-%u\n",stack[0]);
            foundany |= recurse(maxsum, nums, stack, nums[i], i, t);
        }
        if (!foundany) printf("NONE\n");
    }
    return 0;
}
