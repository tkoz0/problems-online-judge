#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
typedef uint32_t u32;
#define MOST_COINS 100
#define MAX_COIN 500

u32 coins[MOST_COINS];
bool possible[1+MAX_COIN*MOST_COINS];

int main(int argc, char **argv)
{
    u32 num_cases;
    int r = scanf("%u",&num_cases);
    assert(r == 1);
    while (num_cases--)
    {
        u32 m;
        r = scanf("%u",&m);
        assert(r == 1);
        assert(m <= MOST_COINS);
        u32 *p = coins;
        u32 sumcoins = 0;
        while (m--) // read coins
        {
            r = scanf("%u",p);
            assert(r == 1 and *p <= MAX_COIN);
            sumcoins += *p;
            ++p;
        }
        for (u32 i = 0; i <= MAX_COIN*MOST_COINS; ++i) possible[i] = 0; // clear
        possible[0] = 1;
        u32 cursum = 0; // sum of previous coins
        for (u32 *cp = coins; cp != p; ++cp) // pointer to current coin
        {
            // if i cents is possible with coins before c, i+c cents is possible
            // go backwards so current coin isnt considered in any assignment
            for (u32 i = 1+cursum; i--;)
                if (possible[i]) possible[i+(*cp)] = 1;
            cursum += *cp;
        }
        assert(cursum == sumcoins);
        // find closest possible in each direction from midpoint
        u32 bestL = sumcoins/2, bestR = sumcoins/2;
        u32 remL = sumcoins-bestL, remR = sumcoins-bestR; // 2nd person amount
        while (!possible[bestL]) --bestL, ++remL;
        while (!possible[bestR]) ++bestR, --remR;
        printf("%u\n",std::min(remL-bestL,bestR-remR));
    }
    return 0;
}
