#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;
typedef double fp;
#define NMAX 8
#define STR_SEP "**********************************************************\n"
#define STR_NET "Network #%u\n"
#define STR_CBLTXT "Cable requirement to connect"
#define STR_CBLFMT "%s (%u,%u) to (%u,%u) is %.2lf feet.\n"
#define STR_REQ "Number of feet of cable required is %.2lf.\n"

struct pt { u32 x, y; };

fp solve_shortest(pt *pts, u32 N)
{
    return 0.0;
}

int main(int argc, char **argv)
{
    static_assert(NMAX >= 2, "NMAX >= 2");
    u32 N, net = 0;
    pt *pts = (pt*) malloc(sizeof(pt) * NMAX);
    while (++net, scanf("%u\n", &N) == 1)
    {
        if (!N) break;
        assert(2 <= N and N <= NMAX);
        for (pt *p = pts; p != pts + N; ++p)
            scanf("%u %u\n", &(p->x), &(p->y));
        printf(STR_SEP);
        printf(STR_NET, net);
        fp result = solve_shortest(pts, N);
        printf(STR_REQ, result);
    }
    free(pts);
    return 0;
}

