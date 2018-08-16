#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
typedef uint32_t u32;
#define MAXD 1000000

char a[MAXD+1], b[MAXD+1]; // storage of 2 numbers (+ space for null terminator)

int main(int argc, char **argv)
{
    u32 N;
    int scanfr = scanf("%u",&N);
    assert(scanfr == 1);
    for (u32 case_num = 0; case_num < N; ++case_num)
    {
        u32 M, z;
        scanfr = scanf("%u",&M);
        assert(scanfr == 1);
        assert(1 <= M and M <= MAXD);
        // numbers are given in big endian
        for (u32 i = 0; i < M; ++i) // read numbers
        {
            scanfr = scanf("%u",&z);
//            assert(scanfr == 1 and z < 10);
            a[i] = z;
            scanfr = scanf("%u",&z);
//            assert(scanfr == 1 and z < 10);
            b[i] = z;
        }
        for (u32 i = M; i--;) a[i] += b[i]; // store sum in char a[]
        for (u32 i = M-1; i--;) // i is position for carry
        {
            a[i] += a[i+1]/10; // carry 1 (without branch / if statement)
            a[i+1] %= 10; // keep lower digit
        }
        for (u32 i = 0; i < M; ++i) a[i] += '0'; // convert to print output
        a[M] = '\0'; // null for string output
        if (case_num) printf("\n");
        printf("%s\n",a);
    }
    return 0;
}
