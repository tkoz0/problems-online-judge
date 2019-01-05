#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>
#include <set>

int main(int argc, char **argv)
{
    uint32_t t, N, M, X, Y, z, xi, r, c1, c2, count;
    int scanfr = scanf("%u",&t);
    assert(scanfr == 1);
    assert(t <= 15);
    std::vector<std::string> matrix;
    std::vector<std::string> search;
    std::string line;
    while (t--) // for each case
    {
        matrix.clear();
        search.clear();
        scanfr = scanf("%u%u",&N,&M);
        assert(scanfr == 2);
        assert(N and M and N <= 1000 and M <= 1000);
        std::getline(std::cin,line); // finish blank line
        for (z = N; z--;) // read matrix rows
        {
            std::getline(std::cin,line);
assert(line.length() >= M); // changing to == causes runtime error
            matrix.push_back(line);
        }
        scanfr = scanf("%u%u",&X,&Y);
        assert(scanfr == 2);
        assert(X and Y and X <= 100 and Y <= 100);
        std::getline(std::cin,line); // finish blank line
        for (z = X; z--;) // read search matrix rows
        {
            std::getline(std::cin,line);
assert(line.length() >= Y); // changing to == causes runtime error
            search.push_back(line);
        }
        if (X > M or Y > N)
        {
            printf("0\n");
            continue;
        }
        // map each string in search to its locations in matrix
        // time complexity should be O(XNM)
        std::vector<std::set<std::pair<uint32_t,uint32_t> > > data(X);
        for (xi = 0; xi != X; ++xi)
            for (r = 0; r != N+1 - (X-xi); ++r) // row in matrix
            {
                for (c1 = 0; c1 != M+1 - Y; ++c1) // start column
                {
                    for (c2 = c1; c2 != c1 + Y; ++c2) // compare string
                    {
                        if (search[xi][c2-c1] != matrix[r][c2])
                            goto next;
                    }
                    data[xi].insert(std::make_pair(r,c1));
                    next:;
                }
            }
        // match search to matrix
        count = 0;
        for (auto u32p : data[0]) // start in first row
        {
            for (xi = 1; xi != X; ++xi)
            {
                if (data[xi].find(std::make_pair(u32p.first+xi,u32p.second))
                    == data[xi].end())
                    goto next2;
            }
            ++count;
            next2:;
        }
        printf("%u\n",count);
    }
    return 0;
}
