#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <ctype.h>
typedef uint32_t u32;
typedef int32_t i32;

u32 col_to_num(const std::string& s)
{
    assert(s.size());
    u32 p = 1; // how many come before: 26^1+26^2+...+26^(len-1)
    for (u32 i = 0; i != s.size(); ++i) p *= 26;
    --p;
    p /= 25;
    --p; // since before, p = 1+26^1+...+26^(len-1)
    u32 b = 1; // base multiplier
    for (u32 i = s.size(); i--;) // add letter value in base26
    {
        assert('A' <= s[i] and s[i] <= 'Z');
        p += b*((u32)(s[i]-'A'));
        b *= 26;
    }
    return p+1; // increment by 1 since AAA..A should be 1 not 0
}

void quick_test()
{
    std::string a="A", z="Z", aa="AA", zz="ZZ", aaa="AAA", zzz="ZZZ";
    assert(col_to_num(a) == 1);
    assert(col_to_num(z) == 26);
    assert(col_to_num(aa) == 27);
    assert(col_to_num(zz) == 702); // 26+26^2
    assert(col_to_num(aaa) == 703);
    assert(col_to_num(zzz) == 18278);
}

#define RMAX 999
#define CMAX 18278
std::string SS[RMAX+1][CMAX+1];
i32 values[RMAX+1][CMAX+1];
bool computed[RMAX+1][CMAX+1];

void debug_print(u32 R, u32 C)
{
    for (u32 i = 1; i <= R; ++i)
    {
        for (u32 j = 1; j <= C; ++j)
            std::cout << SS[i][j] << " ";
        std::cout << std::endl;
    }
}

void compute(u32 r, u32 c) // no cyclic dependencies so recursively compute
{
    if (SS[r][c][0] == '=') // formula
    {
        u32 si = 0;
        i32 sum = 0;
        while (si != SS[r][c].length()) // parse each cell added
        {
            u32 si2 = si+1;
            while (si2 != SS[r][c].length() and isalpha(SS[r][c][si2])) ++si2;
            u32 c2 = col_to_num(SS[r][c].substr(si+1,si2-si-1)); // column
            si = si2;
            while (si2 != SS[r][c].length() and isdigit(SS[r][c][si2])) ++si2;
            u32 r2 = std::stoi(SS[r][c].substr(si,si2-si));
            si = si2;
            if (not computed[r2][c2]) compute(r2,c2);
            sum += values[r2][c2];
        }
        values[r][c] = sum;
    }
    else values[r][c] = std::stoi(SS[r][c]);
    computed[r][c] = 1;
}

int main(int argc, char **argv)
{
    quick_test();
    u32 num_spreadsheets;
    if (scanf("%u",&num_spreadsheets) != 1) assert(0);
    while (num_spreadsheets--)
    {
        u32 R,C;
        if (scanf("%u%u",&C,&R) != 2) assert(0); // c then r order
        assert(1 <= R and R <= RMAX and 1 <= C and C <= CMAX);
        for (u32 i = 1; i <= R; ++i)
            for (u32 j = 1; j <= C; ++j)
            {
                std::cin >> SS[i][j];
                computed[i][j] = 0;
            }
        // debug_print(R,C);
        for (u32 i = 1; i <= R; ++i)
            for (u32 j = 1; j <= C; ++j)
                if (not computed[i][j]) compute(i,j);
        for (u32 i = 1; i <= R; ++i)
        {
            printf("%u",values[i][1]);
            for (u32 j = 2; j <= C; ++j)
                printf(" %u",values[i][j]);
            printf("\n");
        }
    }
    return 0;
}
