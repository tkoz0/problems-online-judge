#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string>
#include <iostream>
typedef uint32_t u32;

int main(int argc, char **argv)
{
    std::string line;
    u32 case_num = 0;
    while (++case_num, 1)
    {
        std::getline(std::cin,line);
        if (line == "") std::getline(std::cin,line); // try again
        if (line == "") break; // should be EOF
        u32 n;
        int r = scanf("%u",&n);
        assert(r == 1);
        printf("Case %u:\n",case_num);
        while (n--)
        {
            u32 i, j;
            r = scanf("%u %u",&i,&j);
            assert(r == 2);
            if (i > j) std::swap(i,j);
            bool same = 1;
            for (u32 k = i+1; k <= j; ++k)
                if (line[k] != line[i])
                {
                    same = 0;
                    break;
                }
            if (same) printf("Yes\n");
            else printf("No\n");
        }
    }
}
