#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
typedef uint32_t u32;
typedef int32_t i32;

inline i32 gcd(i32 a, i32 b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a < b) std::swap(a,b);
    while (b)
    {
        i32 t = a%b;
        a = b;
        b = t;
    }
    return a;
}

inline std::pair<i32,i32> slope(std::pair<i32,i32> p, std::pair<i32,i32> q)
{
    i32 dx = q.first - p.first;
    i32 dy = q.second - p.second;
    if (dx == 0) return std::make_pair(0,1);
    i32 g = gcd(dx,dy);
    dx /= g;
    dy /= g;
    if (dx < 0) dx = -dx, dy = -dy;
    return std::make_pair(dx,dy);
}

struct hash
{
    inline size_t operator()(std::pair<i32,i32> p) const
    {
        return p.first ^ p.second;
    }
};

// uniquely represent line, a,b are not both zero
// if a!=0 pick a postive, otherwise pick b positive
struct line
{
    i32 a,b,c;
    bool operator==(const line& l) const
    {
        return a == l.a and b == l.b and c == l.c;
    }
};

struct line_hash
{
    inline size_t operator()(line l) const
    {
        return l.a ^ l.b ^ l.c;
    }
};

typedef std::unordered_set<std::pair<i32,i32>,hash> point_set;

u32 answer3(std::vector<std::pair<i32,i32> >& points)
{
    std::unordered_map<line,point_set,line_hash> lines;
    i32 a,b,c,g;
    for (u32 i = 1; i < points.size(); ++i)
        for (u32 j = 0; j < i; ++j)
        {
            // taken from first solution
            a = points[j].second - points[i].second;
            b = points[i].first - points[j].first;
            c = points[i].first * points[j].second
              - points[j].first * points[i].second;
            g = gcd(gcd(a,b),c); // since a,b not both zero
            a /= g;
            b /= g;
            c /= g;
            if (a == 0) // pick b to be positive
            {
                if (b < 0) b = -b, c = -c;
            }
            else if (a < 0) a = -a, b = -b, c = -c; // pick a positive
            line l = {a,b,c};
            if (lines.find(l) != lines.end()) lines[l].insert(points[i]);
            else
            {
                lines[l] = point_set();
                lines[l].insert(points[i]);
                lines[l].insert(points[j]);
            }
        }
    u32 best = 0;
    for (auto itr = lines.begin(); itr != lines.end(); ++itr)
        best = std::max(best,(u32)itr->second.size());
    return best;
}

typedef std::unordered_map<std::pair<i32,i32>,point_set,hash> slope_to_points;

// this is too slow for the online judge
u32 answer2(std::vector<std::pair<i32,i32> >& points)
{
    std::vector<slope_to_points> linesets(points.size());
    for (u32 i = 1; i < points.size(); ++i)
        for (u32 j = 0; j < i; ++j)
        {
            std::pair<i32,i32> s = slope(points[i],points[j]);
            if (linesets[j].find(s) != linesets[j].end())
            {
                linesets[j][s].insert(points[i]);
                linesets[i][s] = linesets[j][s];
            }
            else
            {
                linesets[j][s] = point_set();
                linesets[j][s].insert(points[i]);
                linesets[j][s].insert(points[j]);
                linesets[i][s] = linesets[j][s];
            }
        }
    u32 best = 0;
    for (auto s2p : linesets)
        for (auto itr = s2p.begin(); itr != s2p.end(); ++itr)
            best = std::max(best,(u32)itr->second.size());
    return best;
}

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
//        printf("%u\n",answer(points));
//        printf("%u\n",answer2(points));
        printf("%u\n",answer3(points));
    }
    return 0;
}
