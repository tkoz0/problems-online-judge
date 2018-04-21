#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint32_t u32;
#define SIDE 5
#define MAXN 99

// prints bingo results and returns true if any bingo exists
bool check_bingo(bool sel[SIDE][SIDE], u32 nums[SIDE][SIDE], u32 index)
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
            if (!found_bingo) printf("BINGO #%u\n", index);
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
            if (!found_bingo) printf("BINGO #%u\n", index);
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
        if (!found_bingo) printf("BINGO #%u\n", index);
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
    all = true;
    for (r = 0; r != SIDE; ++r) all &= sel[r][r];
    if (all) // print diagonal bingo
    {
        if (!found_bingo) printf("BINGO #%u\n", index);
        found_bingo = true;
        for (r = 0; r != SIDE; ++r)
        {
            printf("%u,%u,", r+1, r+1);
            if (!nums[r][r]) printf("FREE\n");
            else printf("%u\n", nums[r][r]);
        }
    }
    all = true;
    for (r = 0; r != SIDE; ++r) all &= sel[r][SIDE-1-r];
    if (all) // print diagonal bingo
    {
        if (!found_bingo) printf("BINGO #%u\n", index);
        found_bingo = true;
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
    u32 bingo = 0, called;
    bool selected[SIDE][SIDE];
    while (++bingo, scanf("%u", &nums[0][0]) == 1)
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
        if (check_bingo(selected, nums, bingo))
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
            if (check_bingo(selected, nums, bingo))
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
