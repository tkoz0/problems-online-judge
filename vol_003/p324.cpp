#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint16_t u16;
typedef uint32_t u32;
#define MAX_FACTORIAL 366
#define MAX_DIGITS 781

void b10arrmult(u32 *num, u32 amt)
{
    for (u32 *n = num; n != num + MAX_DIGITS; ++n)
        *n *= amt;
    u32 *a = num, *b = num + 1;
    for (; b != num + MAX_DIGITS; ++a, ++b)
        *b += (*a / 10), *a %= 10;
    *a %= 10; // truncate overflow if necessary
}

void _debug_print_freq_table(u16 **freq)
{
    u32 i = 1;
    for (u16 **fp = freq; fp != freq + MAX_FACTORIAL; ++fp, ++i)
    {
        printf("%3u:", i);
        for (u16 *p = *fp; p != *fp + 10; ++p)
            printf(" %3u", *p);
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    u32 *num = (u32*) calloc(sizeof(u32), MAX_DIGITS);
    u16 **freq = (u16**) malloc(sizeof(u16*) * MAX_FACTORIAL);
    for (u16 **f = freq; f != freq + MAX_FACTORIAL; ++f)
        *f = (u16*) calloc(sizeof(u16), 10); // frequency of decimal digits
    *num = 1; // initialize to 1
    u16 **fp = freq;
    for (u32 m = 1; m <= MAX_FACTORIAL; ++m, ++fp)
    {
        b10arrmult(num, m);
        u32 *start = num + MAX_DIGITS; // find first digit
        while (!*(--start));
        while (start >= num) ++(*fp)[*start--];
    }
//    _debug_print_freq_table(freq);
    u32 N;
    while (scanf("%u\n", &N) == 1)
    {
        if (!N) break;
        assert(N <= MAX_FACTORIAL);
        printf("%u! --\n", N);
        u16 *p = freq[N-1];
        u16 *pp = p, ii = 0;
        for (; pp != p + 5; ++pp, ++ii)
            printf("   (%u)%5u", ii, *pp);
        printf("\n");
        for (; pp != p + 10; ++pp, ++ii)
            printf("   (%u)%5u", ii, *pp);
        printf("\n");
    }
    free(num);
    for (u16 **f = freq; f != freq + MAX_FACTORIAL; ++f)
        free(*f);
    free(freq);
    return 0;
}
