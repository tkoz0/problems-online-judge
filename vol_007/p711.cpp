#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint32_t u32;

bool possible[1+20000*6];

int main(int argc, char **argv)
{
    // solution with subset sum dynamic programming
    u32 collec = 0;
    u32 m1, m2, m3, m4, m5, m6; // number of each value of marble
    while (++collec, scanf("%u %u %u %u %u %u",&m1,&m2,&m3,&m4,&m5,&m6) == 6)
    {
        if (!m1 and !m2 and !m3 and !m4 and !m5 and !m6) break;
        assert(m1 + m2 + m3 + m4 + m5 + m6 <= 20000);
        u32 marblesum = 1*m1 + 2*m2 + 3*m3 + 4*m4 + 5*m5 + 6*m6;
        printf("Collection #%u:\n",collec);
        if (marblesum % 2 != 0) printf("Can't be divided.\n\n");
        else
        {
            // generate possible sums to see if marblesum/2 is possible
            for (u32 i = 1; i <= marblesum; ++i) possible[i] = 0; // clear
            possible[0] = 1;
            u32 prevsum = 0;
            for (u32 i = 1+prevsum; i--;) // value 1 marbles
                if (possible[i])
                    for (u32 j = i; j <= i+1*m1; j += 1) possible[j] = 1;
            prevsum += 1*m1;
            for (u32 i = 1+prevsum; i--;) // value 1 marbles
                if (possible[i])
                    for (u32 j = i; j <= i+2*m2; j += 2) possible[j] = 1;
            prevsum += 2*m2;
            for (u32 i = 1+prevsum; i--;) // value 1 marbles
                if (possible[i])
                    for (u32 j = i; j <= i+3*m3; j += 3) possible[j] = 1;
            prevsum += 3*m3;
            for (u32 i = 1+prevsum; i--;) // value 1 marbles
                if (possible[i])
                    for (u32 j = i; j <= i+4*m4; j += 4) possible[j] = 1;
            prevsum += 4*m4;
            for (u32 i = 1+prevsum; i--;) // value 1 marbles
                if (possible[i])
                    for (u32 j = i; j <= i+5*m5; j += 5) possible[j] = 1;
            prevsum += 5*m5;
            for (u32 i = 1+prevsum; i--;) // value 1 marbles
                if (possible[i])
                    for (u32 j = i; j <= i+6*m6; j += 6) possible[j] = 1;
            prevsum += 6*m6;
            if (possible[marblesum/2]) printf("Can be divided.\n\n");
            else printf("Can't be divided.\n\n");
//            printf("::");
//            for (u32 i = 0; i <= marblesum; ++i) printf(" %u",possible[i]);
//            printf("\n");
        }
    }
    return 0;
}
