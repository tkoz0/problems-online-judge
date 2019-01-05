#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    uint32_t cases;
    int r = scanf("%u",&cases);
    assert(cases and cases <= 100);
    uint32_t *odds = (uint32_t*)malloc(sizeof(uint32_t)*cases);
    for (uint32_t *p = odds; p != odds+cases; ++p) // read inputs
    {
        r = scanf("%u",p);
        assert(r == 1);
    }
    // try all possible linear congruential generators allowed
    uint32_t a,b;
    for (a = 0; a <= 10000; ++a)
        for (b = 0; b <= 10000; ++b)
        {
            uint32_t rand = odds[0], i;
            for (i = 1; i != cases; ++i)
            {
                rand = (a*rand + b) % 10001;
                rand = (a*rand + b) % 10001;
                if (rand != odds[i]) break;
            }
            if (i == cases) // reached end successfully
                goto done;
        }
    done: // a,b values known
    for (uint32_t i = 0; i != cases; ++i)
        printf("%u\n",(a*odds[i]+b)%10001);
    return 0;
}
