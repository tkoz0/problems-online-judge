#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

typedef uint32_t u32;

std::vector<std::string> nums;

// generates numbers simply by generating perfect squares and checking them
// using C++ io for convenience to save strings for output
void generate()
{
    u32 rootmax = 1;
    for (u32 d = 1; d <= 4; ++d)
    {
        rootmax *= 10;
        for (u32 r = 0; r < rootmax; ++r)
        {
            u32 s = r * r;
            if (r == (s / rootmax) + (s % rootmax))
            {
                std::stringstream ss;
                ss << std::setfill('0') << std::setw(d << 1) << s;
                nums.push_back(ss.str());
            }
        }
    }
}

int main(int argc, char **argv)
{
    generate();
    u32 n;
    while (scanf("%u", &n) == 1)
        for (auto i = nums.begin(); i != nums.end(); ++i)
            if (i->length() == n)
                std::cout << *i << std::endl;
    return 0;
}
