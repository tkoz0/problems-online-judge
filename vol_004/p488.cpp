#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t u32;

const char *strs[10] = {"", "1", "22", "333", "4444", "55555", "666666",
                        "7777777", "88888888", "999999999"};

int main(int argc, char **argv)
{
    u32 cases, casenum = 0;
    int r = scanf("%u",&cases);
    assert(r == 1);
    u32 a, f;
    while (scanf("%u %u",&a,&f) == 2)
    {
        ++casenum;
        while (f--)
        {
            for (u32 z = 1; z <= a; ++z) printf("%s\n",strs[z]);
            for (u32 z = a; z--;)
            {
                // no blank line after last one
                if (!z and !f and casenum == cases) continue;
                printf("%s\n",strs[z]);
            }
        }
    }
    assert(casenum == cases);
    return 0;
}
