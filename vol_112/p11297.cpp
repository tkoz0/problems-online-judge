#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t data[500][500];

int main(int argc, char **argv)
{
    uint32_t N, Q, i, j, x1, y1, x2, y2, v, min, max;
    int r;
    char c;
    while (scanf("%u",&N) == 1)
    {
        assert(N <= 500);
        for (i = 0; i < N; ++i) // read grid
            for (j = 0; j < N; ++j)
            {
                r = scanf("%u",&data[i][j]);
                assert(r == 1);
            }
        r = scanf("%u",&Q);
        assert(r == 1);
        while (Q--) // process queries
        {
            r = scanf("%c",&c);
            assert(r == 1 && c == '\n');
            r = scanf("%c",&c);
            assert(r == 1);
            if (c == 'q')
            {
                r = scanf("%u%u%u%u",&x1,&y1,&x2,&y2);
                assert(r == 4);
                assert(x1 and y1); // both positive
                assert(x1 <= x2 and x2 <= N and y1 <= y2 and y2 <= N); // bounds
                min = -1, max = 0;
                for (i = x1-1; i < x2; ++i)
                    for (j = y1-1; j < y2; ++j)
                    {
                        if (data[i][j] < min) min = data[i][j];
                        if (data[i][j] > max) max = data[i][j];
                    }
                printf("%u %u\n",max,min);
            }
            else if (c == 'c')
            {
                r = scanf("%u%u%u",&x1,&y1,&v);
                assert(r == 3);
                assert(x1 and y1);
                assert(x1 <= N and y1 <= N);
                data[x1-1][y1-1] = v;
            }
            else assert(0);
        }
    }
    return 0;
}
