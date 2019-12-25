#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
typedef uint32_t u32;

#define MAX_A 200

void _check_cubes2(std::vector<std::vector<std::pair<u32,u32> > >& cubes2)
{
    bool has = false; // check for 113^3+166^3 (specific debugging issue)
    std::vector<std::pair<u32,u32> > vec = cubes2[113*113*113+166*166*166];
    assert(vec.size() > 0);
    for (auto p : vec)
        if (p.first == 113 and p.second == 166)
            has = true;
    assert(has);
    std::vector<std::pair<u32,u32> > vec2 = cubes2[46*46*46+188*188*188];
    for (auto p : vec2) printf("%u,%u\n",p.first,p.second);
}

int main(int argc, char **argv)
{
    std::vector<std::vector<std::pair<u32,u32> > > cubes2(MAX_A*MAX_A*MAX_A);
    for (u32 c = 2; c*c*c <= MAX_A*MAX_A*MAX_A/2; ++c)
        for (u32 d = c+1; c*c*c+d*d*d < MAX_A*MAX_A*MAX_A; ++d)
            cubes2[c*c*c+d*d*d].push_back(std::make_pair(c,d));
//_check_cubes2(cubes2);
    for (u32 a = 2; a <= MAX_A; ++a) // main loop
        for (u32 b = 2; b*b*b <= a*a*a/3; ++b) // find smallest b
        {
            u32 needed = a*a*a - b*b*b; // need c*c*c+d*d*d=needed
            for (auto itr = cubes2[needed].begin(); itr != cubes2[needed].end();
                ++itr)
            {
                u32 c = itr->first;
                u32 d = itr->second;
                //assert(c <= d);
                if (b <= c)
                {
                    assert(a*a*a == b*b*b+c*c*c+d*d*d);
                    assert(b <= c and c <= d);
                    printf("Cube = %u, Triple = (%u,%u,%u)\n",a,b,c,d);
                    //break;
                }
            }
        }
    return 0;
}
