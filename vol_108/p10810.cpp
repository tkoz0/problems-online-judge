#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

uint32_t arr[500000];
uint32_t tmp[500000];

// brute force O(n^2) for debugging
uint32_t count_inversions0(uint32_t beg, uint32_t end)
{
    uint32_t invs = 0;
    for (uint32_t i = beg; i != end; ++i)
        for (uint32_t j = i+1; j != end; ++j)
            if (arr[i] > arr[j]) ++invs;
    return invs;
}

// count inversions in the range [beg,end)
// this one uses a merge sort method
uint32_t count_inversions1(uint32_t beg, uint32_t end)
{
    if (beg+1 >= end) return 0; // no inversions in empty or length 1 array
    uint32_t mid = (beg+end)>>1; // split to [beg,mid) and [mid,end)
    // recursively count inversions undone in the 2 halves
    uint32_t invs = count_inversions1(beg,mid) + count_inversions1(mid,end);
    // merge the 2 halves into tmp and count the inversions undone
    uint32_t L = beg, R = mid; // next index in each half
    for (uint32_t T = beg; T != end; ++T) // index in tmp
    {
        if (L != mid and (R == end or arr[L] < arr[R]))
        // no undone inversions
            tmp[T] = arr[L++]; // pick from left, right empty or left smaller
        else // element moves behind remainder of left side
        {
            tmp[T] = arr[R++]; // pick from right, left is empty
            invs += mid - L;
        }
    }
    // copy sorted data to original array
    for (uint32_t i = beg; i != end; ++i)
        arr[i] = tmp[i];
    return invs;
}

int main(int argc, char **argv)
{
    uint32_t n, *p;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        assert(n < 500000);
        for (p = arr; p != arr+n; ++p)
            scanf("%u",p);
        printf("insertion %u\n",count_inversions0(0,n));
        printf("merge %u\n",count_inversions1(0,n));
//        printf("%u\n",count_inversions1(0,n));
    }
    return 0;
}
