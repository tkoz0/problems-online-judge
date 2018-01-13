#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include <vector>

typedef uint32_t u32;
#define LIMIT 100
#define PER_LINE 15

// small problem, use a pre-created list of primes
std::vector<u32> primes {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

int main(int argc, char **argv)
{
    u32 N;
    bool eof = false;
    // for counting all primes
    std::vector<u32> counts(primes.size());
    while (scanf("%u\n", &N) == 1)
    {
        if (!N)
        {
            eof = true;
            break;
        }
        assert(2 <= N and N <= LIMIT);
        // fill counts array with zeroes
        for (auto i = counts.begin(); i != counts.end(); ++i) *i = 0;
        // count prime factors
        for (auto pi = primes.begin(), ci = counts.begin();
            pi != primes.end(); ++pi, ++ci)
        {
            u32 count = 0, factor = *pi;
            while (factor <= N)
                count += N / factor, factor *= *pi;
            *ci = count;
        }
        // write formatted output
        printf("%3u! =", N);
        u32 printed = 0;
        for (auto i = counts.begin(); i != counts.end() and *i;) // cant be 0
        {
            printf("%3u", *i);
            ++printed, ++i;
            if (printed == PER_LINE)
            {
                printed = 0;
                if (i != counts.end() and *i) // still more to print
                    printf("\n      ");
            }
        }
        printf("\n");
    }
    assert(eof);
    return 0;
}
