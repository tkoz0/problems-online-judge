#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

struct data_t
{
    std::string s;
    uint32_t pos, invs;
    data_t(uint32_t pos = 0) { this->pos = pos; invs = 0; }
    ~data_t(){}
};

int main(int argc, char **argv)
{
    uint32_t M;
    int r = scanf("%u",&M);
    assert(r == 1);
    std::string line;
    while (M--)
    {
        uint32_t n, m;
        r = scanf("%u%u",&n,&m);
        assert(r == 2);
        std::getline(std::cin,line); // finish line with n,m
        std::vector<data_t> data; // m strings
        for (uint32_t i = 0; i < m; ++i) // read strings
        {
            data.push_back(data_t(i));
            std::getline(std::cin,line);
            assert(line.length() == n);
            data[i].s = line;
            // just count inversions by brute force
            uint32_t invs = 0;
            for (uint32_t z1 = 0; z1 < n; ++z1)
                for (uint32_t z2 = z1+1; z2 < n; ++z2)
                    if (line[z1] > line[z2]) ++invs;
            data[i].invs = invs;
        }
        std::sort(data.begin(),data.end(),[](const data_t& a, const data_t& b)
            {
                if (a.invs != b.invs) return a.invs < b.invs; // inversions
                return a.pos < b.pos; // input position
            });
        for (auto d : data)
            printf("%s\n",d.s.c_str());
        if (M) printf("\n");
    }
    return 0;
}
