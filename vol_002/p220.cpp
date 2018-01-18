#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define GRID_SIZE 8
#define NO_LEGAL "No legal move."

inline char other(char turn)
{
    if (turn == 'W') return 'B';
    assert(turn == 'B');
    return 'W';
}

void write_grid(char **grid)
{
    for (char **rp = grid; rp != grid + GRID_SIZE; ++rp)
    {
        for (char *cp = *rp; cp != *rp + GRID_SIZE; ++cp)
            printf("%c", *cp);
        printf("\n");
    }
}

inline bool follow_path(char **grid, char turn, uint32_t r, uint32_t c,
    uint32_t dr, uint32_t dc)
{
    // search for same color along path
    while (r += dr, c += dc, r < GRID_SIZE and c < GRID_SIZE)
    {
        if (grid[r][c] == '-') return false;
        if (grid[r][c] == turn) return true;
    }
    return false; // did not find color
}

inline bool is_legal(char **grid, char turn, uint32_t r, uint32_t c)
{
    bool legal = false;
    char o = other(turn);
    // m,n indicates deltas for r and c along path (one of 8 directions)
    if (r < GRID_SIZE - 2 and grid[r+1][c] == o
        and follow_path(grid, turn, r, c, 1, 0)) legal = true; // +1,0
    if (r > 1 and grid[r-1][c] == o
        and follow_path(grid, turn, r, c, -1, 0)) legal = true; // -1,0
    if (c < GRID_SIZE - 2 and grid[r][c+1] == o
        and follow_path(grid, turn, r, c, 0, 1)) legal = true; // 0,+1
    if (c > 1 and grid[r][c-1] == o
        and follow_path(grid, turn, r, c, 0, -1)) legal = true; // 0,-1
    if (r < GRID_SIZE - 2 and c < GRID_SIZE - 2 and grid[r+1][c+1] == o
        and follow_path(grid, turn, r, c, 1, 1)) legal = true; // +1,+1
    if (r < GRID_SIZE - 2 and c > 1 and grid[r+1][c-1] == o
        and follow_path(grid, turn, r, c, 1, -1)) legal = true; // +1,-1
    if (r > 1 and c < GRID_SIZE - 2 and grid[r-1][c+1] == o
        and follow_path(grid, turn, r, c, -1, 1)) legal = true; // -1,+1
    if (r > 1 and c > 1 and grid[r-1][c-1] == o
        and follow_path(grid, turn, r, c, -1, -1)) legal = true; // -1,-1
    return legal;
}

void list_possible(char **grid, char turn)
{
    bool printed_first = false;
    uint32_t r = 0, c;
    for (char **rp = grid; rp != grid + GRID_SIZE; ++rp, ++r)
    {
        c = 0;
        for (char *cp = *rp; cp != *rp + GRID_SIZE; ++cp, ++c)
        {
            if (*cp != '-') continue; // must be empty
            if (is_legal(grid, turn, r, c))
            {
                if (printed_first) printf(" (%u,%u)", r+1, c+1);
                else
                {
                    printf("(%u,%u)", r+1, c+1);
                    printed_first = true;
                }
            }
        }
    }
    if (!printed_first) printf("%s", NO_LEGAL);
    printf("\n");
}

void make_move(char **grid, char *turn, uint32_t r, uint32_t c)
{
    ;
}

char next_ch()
{
    char c;
    while (scanf("%c", &c) == 1)
        if (c != ' ' and c != '\n') // skip whitespace
            return c;
    return '\0'; // for EOF
}

int main(int argc, char **argv)
{
    static_assert(2 <= GRID_SIZE and GRID_SIZE < 10,
        "2 <= GRID_SIZE and GRID_SIZE < 10\n");
    char **grid = (char**) malloc(GRID_SIZE * sizeof(char*));
    for (char **rp = grid; rp != grid + GRID_SIZE; ++rp)
        *rp = (char*) malloc(GRID_SIZE * sizeof(char));
    uint32_t N;
    int r = scanf("%u\n", &N);
    assert(r == 1 and N);
    while (N--) // process N games
    {
        // read grid
        for (char **rp = grid; rp != grid + GRID_SIZE; ++rp)
            for (char *cp = *rp; cp != *rp + GRID_SIZE; ++cp)
            {
                *cp = next_ch();
                assert(*cp == 'B' or *cp == 'W' or *cp == '-');
            }
        write_grid(grid);
        char turn = next_ch();
        assert(turn == 'B' or turn == 'W');
        // process instructions until quit (Q)
        char instr;
        // scanf before checking condition (use last comma separated statement)
        while ((instr = next_ch()))
        {
            if (instr == 'L')
                list_possible(grid, turn);
            else if (instr == 'M')
            {
                char _r = next_ch();
                char _c = next_ch();
                assert('0' <= _r and _r < '0' + GRID_SIZE);
                assert('0' <= _c and _c < '0' + GRID_SIZE);
                make_move(grid, &turn, _r - '0', _c - '0');
            }
            else
            {
                assert(instr == 'Q');
                break;
            }
        }
    }
    // free memory
    for (char **rp = grid; rp != grid + GRID_SIZE; ++rp)
        free(*rp);
    free(grid);
    return 0;
}

