#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int main(int argc, char **argv)
{
    // compute p^(1/n) (nth root of p), 1 <= p < 10^101
    // specified that all solutions k satisfy 1 <= k <= 10^9
    // k precision needed is small enough that doubles (53 bit precision) works
    // k = p^(1/n)
    double n, p;
    while (scanf("%lf\n%lf\n", &n, &p) == 2)
        printf("%.0lf\n", pow(p, 1.0 / n));
    return 0;
}
