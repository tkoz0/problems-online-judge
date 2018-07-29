#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

typedef uint32_t u32;
typedef int32_t i32;
typedef double fp;

struct point { i32 x, y, z; };

int main(int argc, char **argv)
{
    point p;
    std::vector<point> points;
    while (scanf("%u %u %u",&p.x,&p.y,&p.z) == 3)
    {
        if (!p.x and !p.y and !p.z) break;
        points.push_back(p);
    }
    std::vector<fp> closest;
    for (u32 p1 = 0; p1 < points.size(); ++p1)
    {
        fp mindist = 1000.0F; // guaranteed larger than any
        for (u32 p2 = 0; p2 < points.size(); ++p2)
        {
            if (p1 == p2) continue;
            i32 dx, dy, dz;
            dx = (points[p1].x - points[p2].x);
            dy = (points[p1].y - points[p2].y);
            dz = (points[p1].z - points[p2].z);
            mindist = std::min(mindist,sqrt(dx*dx+dy*dy+dz*dz));
        }
        closest.push_back(mindist);
    }
    u32 histogram[10] = {0,0,0,0,0,0,0,0,0,0};
    for (fp f : closest)
        if (f < 10.0) ++histogram[u32(f)];
    for (u32 i = 0; i < 10; ++i) printf("%4u",histogram[i]);
    printf("\n");
    return 0;
}
