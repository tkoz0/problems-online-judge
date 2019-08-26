#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
typedef uint32_t u32;
typedef int32_t i32;
#define MAX_N 30

int main(int argc, char **argv)
{
    u32 m, n;
    i32 v[3][3], g[3][3];
    // u(x,0)=b1(x) u(x,1)=b2(x) u(0,y)=b3(y) u(1,y)=b4(y)
    i32 b1[1+MAX_N], b2[1+MAX_N], b3[1+MAX_N], b4[1+MAX_N];
    i32 f[1+MAX_N][1+MAX_N];
    u32 P[1+MAX_N][1+MAX_N]; // store the number of the point, 0 for boundary
    u32 xof[(MAX_N-1)*(MAX_N-1)]; // max P to x
    u32 yof[(MAX_N-1)*(MAX_N-1)]; // map P to y
    i32 B[1+MAX_N][1+MAX_N]; // store boundary values
    i32 **a; // reallocated on heap (probably is too much for stack)
    a = malloc(sizeof(*a)*(MAX_N-1)*(MAX_N-1));
    for (u32 z = 0; z < (MAX_N-1)*(MAX_N-1); ++z)
        a[z] = malloc(sizeof(**a)*(MAX_N-1)*(MAX_N-1));
//    i32 a[(MAX_N-1)*(MAX_N-1)][(MAX_N-1)*(MAX_N-1)]; // for solution
    i32 b[(MAX_N-1)*(MAX_N-1)]; // for solution, both solutions offset by 1
    if (scanf("%u",&m) != 1) assert(0); // number of tests
    while (m--)
    {
        if (scanf("%u",&n) != 1) assert(0);
        assert(2 <= n && n <= MAX_N);
        if (scanf("%i%i%i%i%i%i%i%i%i",&v[0][2],&v[1][2],&v[2][2], // v
                &v[0][1],&v[1][1],&v[2][1],&v[0][0],&v[1][0],&v[2][0]) != 9)
            assert(0);
        if (scanf("%i%i%i%i%i%i%i%i%i",&g[0][2],&g[1][2],&g[2][2], // g
                &g[0][1],&g[1][1],&g[2][1],&g[0][0],&g[1][0],&g[2][0]) != 9)
            assert(0);
        for (u32 i = 0; i <= n; ++i) // boundaries
        {
            if (scanf("%i",b1+i) != 1) assert(0);
            B[i][0] = b1[i];
        }
        for (u32 i = 0; i <= n; ++i)
        {
            if (scanf("%i",b2+i) != 1) assert(0);
            B[i][n] = b2[i];
        }
        for (u32 i = 0; i <= n; ++i)
        {
            if (scanf("%i",b3+i) != 1) assert(0);
            B[0][i] = b3[i];
        }
        for (u32 i = 0; i <= n; ++i)
        {
            if (scanf("%i",b4+i) != 1) assert(0);
            B[n][i] = b4[i];
        }
        assert(b1[0] == b3[0]);
        assert(b2[0] == b3[n]);
        assert(b2[n] == b4[n]);
        assert(b1[n] == b4[0]);

        // printf("boundary\n");
        // for (u32 y = n+1; y--;)
        // {
        //     for (u32 x = 0; x <= n; ++x) printf("%i ",B[x][y]);
        //     printf("\n");
        // }
        // printf("end boundary\n");

        for (u32 y = n+1; y--;) // f
            for (u32 x = 0; x <= n; ++x)
                if (scanf("%i",&f[x][y]) != 1) assert(0);

//        continue; // debug

        u32 pnum = 0;
        for (u32 y = n+1; y--;) // setup P matrix
            for (u32 x = 0; x <= n; ++x)
            {
                // boundary
                if (x == 0 || x == n || y == 0 || y == n) P[x][y] = 0;
                else // internal point
                {
                    P[x][y] = ++pnum;
                    xof[pnum] = x;
                    yof[pnum] = y;
                }
            }
        // for each point, computed desired result
        for (u32 p = 1; p <= pnum; ++p)
        {
            for (u32 z = 0; z < pnum*pnum; ++z) // zero matrix row
                a[p-1][z] = 0;
            i32 rhs = 0; // right hand side value
            u32 x = xof[p], y = yof[p];
            for (i32 x2 = -1; x2 <= 1; ++x2) // v and g matrices
                for (i32 y2 = -1; y2 <= 1; ++y2)
                {
//                    printf("p%u adding %i*%i\n",p,g[1+x2][1+y2],f[x+x2][y+y2]);
                    rhs += g[1+x2][1+y2]*f[x+x2][y+y2]; // g contributes to rhs
                    if (P[x+x2][y+y2]) // P number, v contributes to main matrix
                    {
                        a[p-1][P[x+x2][y+y2]-1] = v[1+x2][1+y2] *n*n;
                    }
                    else // get from boundary, contribute to rhs
                    {
//                        printf("p%u subtracting %i\n",p,v[1+x2][1+y2]*B[x+x2][y+y2] *n*n);
                        rhs -= v[1+x2][1+y2]*B[x+x2][y+y2] *n*n;
                    }
                }
            b[p-1] = rhs; // TODO wrong, fix
        }
        // print results
        for (u32 r = 0; r < pnum; ++r)
        {
            printf("%i",a[r][0]);
            for (u32 c = 1; c < pnum; ++c) printf(" %i",a[r][c]);
            printf("\n");
        }
        printf("%i",b[0]);
        for (u32 x = 1; x < pnum; ++x) printf(" %i",b[x]);
        printf("\n");
    }
    return 0;
}
