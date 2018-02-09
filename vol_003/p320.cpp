#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <vector>

typedef uint32_t u32;
#define GRID 32

// write grid bits to output, no header, just the grid only
void print_grid(std::vector<std::vector<bool> >& grid)
{
    for (auto r = grid.rbegin(); r != grid.rend(); ++r)
    {
        for (auto c = r->begin(); c != r->end(); ++c)
        {
            if (*c) printf("X");
            else printf(".");
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    u32 num_test_cases;
    int r = scanf("%u\n", &num_test_cases);
    assert(r == 1 and num_test_cases);
    u32 test_case = 0;
    while (++test_case <= num_test_cases)
    {
        u32 sx, sy;
        r = scanf("%u %u\n", &sx, &sy);
        assert(r == 2);
        assert(sx and sx < GRID);
        assert(sy and sy < GRID);
        // initialize null grid, 0='.', 1='X'
        std::vector<std::vector<bool> > grid(GRID, std::vector<bool>(GRID));
        char c;
        while (r = scanf("%c", &c), c != '.')
        {
            assert(r == 1);
            if (c == ' ' or c == '\n') continue;
            switch (c) // fill space to the right since path is anticlockwise
            {
                case 'E': grid[sy-1][sx++] = 1; break;
                case 'N': grid[sy++][sx] = 1; break;
                case 'W': grid[sy][--sx] = 1; break;
                case 'S': grid[--sy][sx-1] = 1; break;
                default: assert(0);
            }
            assert(sx and sx < GRID);
            assert(sy and sy < GRID);
        }
        r = scanf("%c", &c); // read new line after directions
        assert(r == 1 and c == '\n');
        printf("Bitmap #%u\n", test_case);
        print_grid(grid);
        printf("\n");
    }
    return 0;
}
