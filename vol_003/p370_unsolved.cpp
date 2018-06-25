#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint32_t u32;
#define SIDE 5
#define MAXN 99

// TODO rewrite main() and check_bingo()
// TODO check_bingo()
// - use bools for each possible bingo
// - example: array for the 5 rows, "is bingo in that row"
// - maybe make a bool[][] (like selection array) for selecting print out data
// - do all data printing after checking every possible bingo
// TODO main()
// - should be similar to whats already there, clean it up a bit

void _debug_selection(bool sel[SIDE][SIDE])
{
    for (u32 i = 0; i != SIDE; ++i)
    {
        for (u32 j = 0; j != SIDE; ++j)
            printf("%u ", sel[i][j]);
        printf("\n");
    }
}

void _debug_nums(u32 nums[SIDE][SIDE])
{
    for (u32 i = 0; i != SIDE; ++i)
    {
        for (u32 j = 0; j != SIDE; ++j)
            printf("%2u ", nums[i][j]);
        printf("\n");
    }
}

// prints bingo results and returns true if any bingo exists
bool check_bingo(bool sel[SIDE][SIDE], u32 nums[SIDE][SIDE])
{
    u32 r, c;
    bool found_bingo = false;
    bool all = true;
    // check rows
    for (r = 0; r != SIDE; ++r)
    {
        all = true;
        for (c = 0; c != SIDE; ++c) all &= sel[r][c];
        if (all) // print row bingo
        {
            printf("BINGO #1\n");
            found_bingo = true;
            for (c = 0; c != SIDE; ++c)
            {
                printf("%u,%u,", r+1, c+1);
                if (!nums[r][c]) printf("FREE\n");
                else printf("%u\n", nums[r][c]);
            }
        }
    }
    // check columns
    for (c = 0; c != SIDE; ++c)
    {
        all = true;
        for (r = 0; r != SIDE; ++r) all &= sel[r][c];
        if (all) // print column bingo
        {
            printf("BINGO #2\n");
            found_bingo = true;
            for (r = 0; r != SIDE; ++r)
            {
                printf("%u,%u,", r+1, c+1);
                if (!nums[r][c]) printf("FREE\n");
                else printf("%u\n", nums[r][c]);
            }
        }
    }
    // check corners
    if (sel[0][0] and sel[SIDE-1][0] and sel[0][SIDE-1] and sel[SIDE-1][SIDE-1])
    {
        printf("BINGO #3\n");
        found_bingo = true;
        printf("%u,%u,", 0, 0);
        if (!nums[0][0]) printf("FREE\n");
        else printf("%u\n", nums[0][0]);printf("%u,%u,", 0, 0);
        printf("%u,%u,", SIDE-1, 0);
        if (!nums[SIDE-1][0]) printf("FREE\n");
        else printf("%u\n", nums[SIDE-1][0]);printf("%u,%u,", 0, 0);
        printf("%u,%u,", 0, SIDE-1);
        if (!nums[0][SIDE-1]) printf("FREE\n");
        else printf("%u\n", nums[0][SIDE-1]);printf("%u,%u,", 0, 0);
        printf("%u,%u,", SIDE-1, SIDE-1);
        if (!nums[SIDE-1][SIDE-1]) printf("FREE\n");
        else printf("%u\n", nums[SIDE-1][SIDE-1]);
    }
    // check diagonals
    bool down_right_diag = false; // since 2 diagonals could occur together
    bool down_left_diag = false;
    all = true;
    for (r = 0; r != SIDE; ++r) all &= sel[r][r];
    if (all) // print diagonal bingo
    {
        down_right_diag = true;
        found_bingo = true;
    }
    all = true;
    for (r = 0; r != SIDE; ++r) all &= sel[r][SIDE-1-r];
    if (all) // print diagonal bingo
    {
        down_left_diag = true;
        found_bingo = true;
    }
    if (down_right_diag and down_left_diag)
    {
        printf("BINGO #4\n");
        for (r = 0, c = SIDE-1; r != SIDE; ++r, --c)
        {
            if (r < c)
            {
                printf("%u,%u,", r+1, r+1);
                if (!nums[r][r]) printf("FREE\n");
                else printf("%u\n", nums[r][r]);
                printf("%u,%u,", r+1, c+1);
                if (!nums[r][c]) printf("FREE\n");
                else printf("%u\n", nums[r][c]);
            }
            else if (r > c)
            {
                printf("%u,%u,", r+1, c+1);
                if (!nums[r][c]) printf("FREE\n");
                else printf("%u\n", nums[r][c]);
                printf("%u,%u,", r+1, r+1);
                if (!nums[r][r]) printf("FREE\n");
                else printf("%u\n", nums[r][r]);
            }
            else // r==c
            {
                printf("%u,%u,", r+1, r+1);
                if (!nums[r][r]) printf("FREE\n");
                else printf("%u\n", nums[r][r]);
            }
        }
    }
    else if (down_right_diag)
    {
        printf("BINGO #4\n");
        for (r = 0; r != SIDE; ++r)
        {
            printf("%u,%u,", r+1, r+1);
            if (!nums[r][r]) printf("FREE\n");
            else printf("%u\n", nums[r][r]);
        }
    }
    else if (down_left_diag)
    {
        if (!down_right_diag) printf("BINGO #4\n");
        for (r = 0; r != SIDE; ++r)
        {
            printf("%u,%u,", r+1, SIDE-1-r);
            if (!nums[r][SIDE-1-r]) printf("FREE\n");
            else printf("%u\n", nums[r][SIDE-1-r]);
        }
    }
    if (found_bingo) printf("\n");
    return found_bingo;
}

int main(int argc, char **argv)
{
    u32 nums[SIDE][SIDE];
    u32 called;
    bool selected[SIDE][SIDE];
    while (scanf("%u", &nums[0][0]) == 1)
    {
        // reset selected array
        for (u32 i = 0; i != SIDE * SIDE; ++i)
            selected[i/SIDE][i%SIDE] = false;
        if (!nums[0][0]) selected[0][0] = true;
        // read 24 other numbers
        for (u32 i = 1; i != SIDE * SIDE; ++i)
        {
            int r = scanf("%u", &nums[i/SIDE][i%SIDE]);
            if (!nums[i/SIDE][i%SIDE]) selected[i/SIDE][i%SIDE] = true;
            assert(r == 1);
        }
        if (check_bingo(selected, nums))
        {
            for (;;) // skip called numbers
            {
                int r = scanf("%u", &called);
                assert(r == 1);
                if (!called) break;
            }
            continue;
        }
        for (u32 i = 0; i != SIDE * SIDE; ++i)
            assert(nums[i/SIDE][i%SIDE] <= MAXN);
        // process called numbers
        for (;;)
        {
            int r = scanf("%u", &called);
            assert(r == 1);
            if (!called) break; // 0 ends called numbers
            for (u32 i = 0; i != SIDE * SIDE; ++i) // select spaces with it
                if (nums[i/SIDE][i%SIDE] == called)
                    selected[i/SIDE][i%SIDE] = true;
            if (check_bingo(selected, nums))
            {
                for (;;) // skip called numbers
                {
                    int r = scanf("%u", &called);
                    assert(r == 1);
                    if (!called) break;
                }
                goto next_card;
            }
        }
        printf("No BINGO on this card.\n\n");
        next_card:;
    }
    return 0;
}
