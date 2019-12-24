#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
typedef uint32_t u32;
typedef int32_t i32;

u32 answer(std::vector<std::pair<i32,i32> >& points)
{
    u32 i,j,k,count,best;
    i32 a,b,c;
    best = 0;
    if (points.size() < 2) return points.size();
    for (i = 0; i < points.size(); ++i)
        for (j = i+1; j < points.size(); ++j)
        {
            // use some ax+by=c line equation
            // points[i] = (x1,y1), points[j] = (x2,y2)
            // rearranging point slope form: (y-y1)(x2-x1)=(y2-y1)(x-x1)
            // --> x(y2-y1)+y(x1-x2) = x1y2 - x2y1 (algebra)
            a = points[j].second - points[i].second;
            b = points[i].first - points[j].first;
            c = points[i].first * points[j].second
              - points[j].first * points[i].second;
            // if (x,y) on this line, then it satisfies ax+by=c
            count = 0;
            for (k = 0; k < points.size(); ++k)
                if (a*points[k].first + b*points[k].second == c) ++count;
            best = std::max(best,count);
        }
    return best;
}

int main(int argc, char **argv)
{
    u32 cases;
    i32 x, y;
    std::string line;
    std::getline(std::cin,line);
    std::stringstream ss(line);
    if (!(ss >> cases)) assert(0);
    std::vector<std::pair<i32,i32> > points;
    for (u32 case_ = 0; case_ < cases; ++case_)
    {
        if (case_ == 0) std::getline(std::cin,line);
        points.clear();
        for (;;)
        {
            std::getline(std::cin,line);
            if (line == "") break;
            ss = std::stringstream(line);
            if (!(ss >> x >> y)) assert(0);
            points.push_back(std::make_pair(x,y));
        }
        assert(points.size() > 0);
        if (case_ != 0) printf("\n");
        printf("%u\n",answer(points));
    }
    return 0;
}
