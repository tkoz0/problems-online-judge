#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>

int main(int argc, char **argv)
{
    int32_t H, M;
    while (scanf("%u:%u",&H,&M) == 2)
    {
        if (!H and !M) break;
        double aH = 30.0*double(H) + 0.5*double(M);
        double aM = 6.0*double(M);
        double dif = std::max(aM,aH) - std::min(aM,aH);
        printf("%.3lf\n",std::min(dif,360.0-dif));
    }
    return 0;
}
