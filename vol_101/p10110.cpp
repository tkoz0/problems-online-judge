#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
typedef uint32_t u32;

bool perf_square(u32 n)
{
    u32 count = 0;
    while (n % 2 == 0) n /= 2, count += 1;
    if (count % 2 == 1) return false;
    u32 d = 3;
    while (d*d <= n)
    {
        if (n % d != 0) { d += 2; continue; }
        count = 1, n /= d;
        while (n % d == 0) n /= d, count += 1;
        if (count % 2 == 1) return false;
        d += 2;
    }
    return n == 1;
}

int main(int argc, char **argv)
{
    u32 n;
    while (scanf("%u",&n) == 1)
    {
        if (!n) break;
        u32 root = u32(sqrt(double(n)));
//        if (perf_square(n)) printf("yes\n");
        if (root*root == n) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
