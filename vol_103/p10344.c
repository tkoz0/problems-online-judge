#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#define GOAL 23

int nums[5];
int mark[5]; // number already used

int search2(int val)
{
    int m = 1;
    for (int i = 0; i < 5; ++i) m &= mark[i];
    if (m) return val == GOAL; // all numbers used
    for (int i = 0; i < 5; ++i)
    {
        if (mark[i]) continue; // already used
        mark[i] = 1;
        if (search2(val+nums[i])) return 1;
        if (search2(val-nums[i])) return 1;
        if (search2(val*nums[i])) return 1;
        mark[i] = 0;
    }
    return 0; // not found
}

int search()
{
    for (int i = 0; i < 5; ++i)
    {
        mark[i] = 1;
        if (search2(nums[i])) return 1;
        mark[i] = 0;
    }
    return 0; // did not find
}

int main(int argc, char **argv)
{
    while (scanf("%d%d%d%d%d",nums+0,nums+1,nums+2,nums+3,nums+4) == 5)
    {
        int a = 0;
        for (int i = 0; i < 5; ++i) a |= nums[i];
        if (a == 0) break; // all input was zero
        for (int i = 0; i < 5; ++i) mark[i] = 0;
        if (search()) printf("Possible\n");
        else printf("Impossible\n");
    }
    return 0;
}
