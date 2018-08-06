#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <queue>
#include <vector>
typedef uint32_t u32;

// -----THIS IS ONLY THE CASE IF WE NEED TO ADD NUMBERS 1 AT A TIME TO SOME
// -----CUMULATIVE SUM BUT PROBLEM ASKS FOR SUMMING NUMBERS BY COMBINING
// -----ANY 2 INTO A LARGE NUMBER AT A COST UNTIL THE TOTAL IS COMPUTED
// greedy algorithm, numbers must be sorted since we get
// n*nums[0] + (n-1)*nums[1] + ... then -nums[0] at end
// to show that sorting is required, suppose there is an inversion and
// that by swapping those 2, a smaller total cost is computed

// proper solution is with a priority queue, pop smallest 2, add, push
// stop when only 1 number remains in the priority queue

struct U32Min
{
    bool operator()(u32 a, u32 b) { return a > b; }
};

int main(int argc, char **argv)
{
    u32 N, z, y, cost;
    std::priority_queue<u32,std::vector<u32>,U32Min> Q;
    while (scanf("%u",&N) == 1)
    {
        if (!N) break;
        assert(2 <= N and N <= 5000);
        assert(Q.empty());
        while (N--)
        {
            scanf("%u",&z);
            Q.push(z);
        }
        cost = 0;
        for (;;)
        {
            z = Q.top();
            Q.pop();
            if (Q.empty()) break;
            y = Q.top();
            Q.pop();
            Q.push(z+y);
            cost += z+y; // sum costs for every combining of 2 numbers
        }
        printf("%u\n",cost);
    }
    return 0;
}
