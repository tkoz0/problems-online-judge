#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

uint32_t maze[1000][1000];

#define MIN(x,y) (x<y?x:y)

int main(int argc, char **argv)
{
    uint32_t count, N, M; // num cases, rows, cols
    scanf("%u",&count);
    while (count--)
    {
        scanf("%u%u",&N,&M);
        assert(N and N <= 999);
        assert(M and M <= 999);
        for (uint32_t i = 0; i < N; ++i)
            for (uint32_t j = 0; j < M; ++j)
                scanf("%u",&maze[i][j]);
        for (uint32_t i = 1; i < N; ++i) maze[i][0] += maze[i-1][0];
        for (uint32_t i = 1; i < M; ++i) maze[0][i] += maze[0][i-1];
        for (uint32_t i = 1; i < N; ++i)
            for (uint32_t j = 1; j < M; ++j)
                maze[i][j] += MIN(maze[i-1][j],maze[i][j-1]);
        printf("%u\n",maze[N-1][M-1]);
    }
    return 0;
}
