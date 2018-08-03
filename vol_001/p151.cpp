#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <list>
typedef uint32_t u32;

int main(int argc, char **argv)
{
    u32 N;
    while (scanf("%u",&N) == 1)
    {
        if (!N) break;
        assert(13 <= N and N < 100);
        std::list<u32> original;
        for (u32 z = 1; z <= N; ++z) original.push_back(z);
        for (u32 m = 1;; ++m) // try each m
        {
//printf("m=%u ",m);
            std::list<u32> l = original;
            auto itr = l.begin();
            while (l.size() > 1)
            {
//printf("%u ",*itr);
                itr = l.erase(itr); // turn off power
                if (itr == l.end()) itr = l.begin();
                // advance iterator m times (m-1 since erase advances it once)
                for (u32 z = 1; z < m; ++z)
                {
                    ++itr;
                    if (itr == l.end()) itr = l.begin(); // cycle around
                }
            }
//printf("%u\n",l.front());
            assert(l.size() == 1);
            if (l.front() == 13)
            {
                printf("%u\n",m);
                break;
            }
        }
    }
    return 0;
}
