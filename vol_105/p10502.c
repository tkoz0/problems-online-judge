#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
typedef uint8_t u8;
typedef uint32_t u32;

u8 board[100][100];

int main(int argc, char **argv)
{
    char ch;
    int _r;
    u32 n,m,r,c,count,r1,r2,consec;
    u8 all1;
    while (scanf("%u%u",&n,&m) == 2)
    {
        _r = scanf("%c",&ch);
        assert(_r == 1 && ch == '\n'); // finish line
        for (r = 0; r < n; ++r) // read lines
        {
            for (c = 0; c < m; ++c)
            {
                scanf("%c",&board[r][c]);
                board[r][c] -= '0';
                assert(board[r][c] < 2);
            }
            _r = scanf("%c",&ch);
            assert(_r == 1 && ch == '\n');
        }
        count = 0; // naive O(n^4) algorithm
        for (r1 = 0; r1 < n; ++r1) // pick 2 rows to sweep
            for (r2 = r1; r2 < n; ++r2)
            {
                consec = 0;
                for (c = 0; c < m; ++c)
                {
                    all1 = 1;
                    for (r = r1; r <= r2; ++r)
                        all1 &= board[r][c];
                    if (all1) count += ++consec;
                    else consec = 0;
                }
            }
        printf("%u\n",count);
    }
}
