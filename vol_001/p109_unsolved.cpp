#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <string>
#include <iostream>

typedef uint32_t u32;
#define COORD_LIMIT 500
#define MAX_KINGDOMS 20
#define MAX_SITES 100

struct pt
{
    u32 x, y;
    pt() {}
    pt(u32 x, u32 y)
    {
        assert(x <= COORD_LIMIT);
        assert(y <= COORD_LIMIT);
        this->x = x;
        this->y = y;
    }
};

struct kingdom
{
    pt _pp; // power plant
    std::vector<pt> _homes;
    kingdom(u32 ppx, u32 ppy)
    {
        this->_pp = pt(ppx, ppy);
    }
    void add_home(u32 x, u32 y)
    {
        this->_homes.push_back(pt(x, y));
    }
};

void _debug_visualize(std::vector<kingdom>& k, std::vector<pt>& m,
    bool show_missiles = true)
{
    // output a visualization grid of the map
    // assume that no kingdoms overlap so visualization shouldnt get messy
    // represent homes of kingdoms with nums 1-9
    // power plants are P and missiles are X
    assert(k.size() <= 9);
    u32 xlim = 0, ylim = 0;
    for (auto ki = k.begin(); ki != k.end(); ++ki)
    {
        if (ki->_pp.x > xlim) xlim = ki->_pp.x;
        if (ki->_pp.y > ylim) ylim = ki->_pp.y;
        for (auto hi = ki->_homes.begin(); hi != ki->_homes.end(); ++hi)
        {
            if (hi->x > xlim) xlim = hi->x;
            if (hi->y > ylim) ylim = hi->y;
        }
    }
    for (auto mi = m.begin(); mi != m.end(); ++mi)
    {
        if (mi->x > xlim) xlim = mi->x;
        if (mi->y > ylim) ylim = mi->y;
    }
    // create empty grid with spaces
    std::vector<std::string> grid(ylim+1, std::string(xlim+1, ' '));
    u32 index = 1;
    for (auto ki = k.begin(); ki != k.end(); ++ki, ++index)
    {
        // add homes and power plants to grid
        grid[ki->_pp.y][ki->_pp.x] = 'P';
        for (auto hi = ki->_homes.begin(); hi != ki->_homes.end(); ++hi)
            grid[hi->y][hi->x] = '0' + index;
    }
    for (auto mi = m.begin(); mi != m.end(); ++mi)
        grid[mi->y][mi->x] = 'X'; // place missiles
    // output
    for (auto li = grid.begin(); li != grid.end(); ++li)
        std::cout << *li << std::endl;
}

void _debug_print(std::vector<kingdom>& k, std::vector<pt>& m)
{
    for (u32 i = 0; i != k.size(); ++i)
    {
        printf("k%02u(%u,%u):", i+1, k[i]._pp.x, k[i]._pp.y);
        for (auto j = k[i]._homes.begin(); j != k[i]._homes.end(); ++j)
            printf(" (%u,%u)", j->x, j->y);
        printf("\n");
    }
    printf("missiles:");
    for (auto i = m.begin(); i != m.end(); ++i)
        printf(" (%u,%u)", i->x, i->y);
    printf("\n");
}

int main(int argc, char **argv)
{
    u32 N; // number of sites
    bool read_missiles = false; // change to true after N value read is -1
    std::vector<kingdom> kingdoms;
    std::vector<pt> missiles;
    while (scanf("%u\n", &N) == 1)
    {
        if (N == -1) // end of kingdom inputs
        {
            read_missiles = true;
            break;
        }
        assert(N >= 3 and N <= MAX_SITES);
        // read power plant and N-1 homes
        u32 x, y;
        int r = scanf("%u %u\n", &x, &y);
        assert(r == 2);
        kingdom k(x, y); // make kingdom with power plant coordinates
        for (u32 i = 1; i != N; ++i) // read N-1 homes
        {
            r = scanf("%u %u\n", &x, &y);
            assert(r == 2);
            k.add_home(x, y);
        }
        kingdoms.push_back(k);
    }
    assert(kingdoms.size() <= MAX_KINGDOMS);
    assert(read_missiles); // should have reached a N=-1 kingdom before this
    u32 x, y;
    while (scanf("%u %u\n", &x, &y) == 2)
        missiles.push_back(pt(x, y));
    _debug_print(kingdoms, missiles);
    _debug_visualize(kingdoms, missiles);
    return 0;
}
