#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// number type for this problem
typedef double nt;
// error allowed for floating point arithmetic
#define DERR 0.000000001

int main(int argc, char **argv)
{
    nt init_h, worker_cats;
    while (scanf("%lf %lf\n", &init_h, &worker_cats) == 2)
    {
        if (init_h == 0.0 and worker_cats == 0.0) break; // 0,0 terminates input
        if (fabs(worker_cats - 1.0) < DERR) // N = 1, handle separately
        {
            nt non_workers = 0.0, stack = 0.0;
            while (fabs(init_h - 1.0) > DERR)
                non_workers += 1.0, stack += init_h, init_h /= 2.0;
            stack += 1.0; // last cat
            printf("%.0lf %.0lf\n", non_workers, stack);
            continue;
        }
        assert(init_h > worker_cats);
        // if L is num levels of cats and N is num cats in each hat
        // line contains (N+1)^L = X and N^L = Y
        // solving gets log(N+1)/logN = logX/logY, differentiation shows that
        // log(N+1)/logN only decreases so continue until it becomes smaller
        // than logX/logY
        nt N = 2.0, xysol = log(init_h) / log(worker_cats);
        for (;; ++N)
        {
            nt val = log(N + 1.0) / log(N);
            if (fabs(val - xysol) < DERR) break; // found within ok error
            if (val < xysol) assert(0); // should not find that no answer exists
        }
//        printf("N=%lf\n", N);
        // L can be computed as L=logY/logN from solving above equations
        nt L = log(worker_cats) / log(N);
//        printf("L=%lf\n", L);
        // compute non working cats as geometric sum (up to level L-1)
        // non working = (1 - N^L) / (1 - N)
        nt non_work = (1.0 - pow(N, L)) / (1.0 - N);
        // cat stack height cat be computed by summing each level
        nt stack_ht = init_h, cats_on_level = 1.0;
        while ((init_h /= (N + 1)) > 1.0 - DERR) // until last level of height 1
            stack_ht += init_h * (cats_on_level *= N);
        printf("%.0lf %.0lf\n", non_work, stack_ht); // output answer
    }
    return 0;
}
