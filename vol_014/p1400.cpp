#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int32_t dishes[500000];

int main(int argc, char **argv)
{
    uint32_t n, m, case_n = 0;
    while (++case_n, scanf("%u%u",&n,&m) == 2)
    {
        assert(n < 500000 and m < 500000);
        for (int32_t *p = dishes; p != dishes+n; ++p) // dish values
            scanf("%u",p);
        printf("Case %u:\n",case_n);
        while (m--) // process questions
        {
            uint32_t a, b;
            scanf("%u%u",&a,&b);
            --a, --b; // convert to 0 indexing
            assert(a <= b and b < n);
            uint32_t beg = a, end;
            int64_t sum = 0;
            uint32_t best_a = -1, best_b = -1;
            int64_t best_sum = 0;
            for (end = a; end <= b; ++end)
            {
                sum += dishes[end];
                if (sum <= 0) // restart
                {
                    sum = 0;
                    beg = end+1;
                }
                if (sum > best_sum) // better subsequence
                {
                    best_sum = sum;
                    best_a = beg;
                    best_b = end;
                }
            }
            assert(best_a != -1 and best_b != -1);
            printf("%u %u\n",best_a+1,best_b+1);
        }
    }
    return 0;
}
