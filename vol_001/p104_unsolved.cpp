#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;
typedef double fp;
#define NO_SEQ "no arbitrage sequence exists"
#define MOST_CURRENCY 20
#define PROFIT_FACTOR 1.01

void _debug_print_table(fp **t, u32 n)
{
    assert(n <= MOST_CURRENCY);
    for (fp **rp = t; rp != t + n; ++rp)
    {
        for (fp *cp = *rp; cp != *rp + n; ++cp)
            printf("%06.2lf ", *cp);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    u32 n;
    // allocate table of largest size needed
    fp **table = (fp**) malloc(MOST_CURRENCY * sizeof(fp*));
    for (fp **rp = table; rp != table + MOST_CURRENCY; ++rp)
        *rp = (fp*) malloc(MOST_CURRENCY * sizeof(fp));
    while (scanf("%u\n", &n) == 1)
    {
        assert(n >= 2 and n <= MOST_CURRENCY);
        // read files from input
        for (u32 a = 0; a != n; ++a)
            for (u32 b = 0; b != n; ++b)
            {
                if (a == b) table[a][b] = 1.0; // currency convert to itself
                else
                {
                    int r = scanf("%lf", &(table[a][b])); // read from stdin
                    assert(r == 1);
                }
            }
//        _debug_print_table(table, n);
    }
    // clean up memory
    for (fp **rp = table; rp != table + MOST_CURRENCY; ++rp)
        free(*rp);
    free(table);
    return 0;
}
