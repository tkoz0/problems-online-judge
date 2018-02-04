#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
typedef uint32_t u32;
#define MAX_PACKET 6
#define PARCEL 6

inline bool zero(const u32 *arr)
{
    for (const u32 *p = arr; p != arr + MAX_PACKET; ++p)
        if (*p) return false;
    return true;
}

void _print_parcel(bool box[PARCEL][PARCEL])
{
    for (u32 x = 0; x != PARCEL; ++x)
    {
        for (u32 y = 0; y != PARCEL; ++y)
        {
            if (box[x][y]) printf("* ");
            else printf("- ");
        }
        printf("\n");
    }
}

u32 parcels(u32 *arr)
{
    bool box[PARCEL][PARCEL];
    u32 count = 0;
    while (not zero(arr)) // process until all packets are in parcels
    {
//        printf("create parcel\n");
        ++count; // create new parcel
        memset(box, 0, PARCEL * PARCEL * sizeof(bool));
        u32 size = MAX_PACKET;
        for (u32 *p = arr + MAX_PACKET; p-- != arr; --size)
        {
            // try to fit packets into parcel, starting with largest
            // top left corner
            for (u32 x = 0; x <= PARCEL - size; ++x)
                for (u32 y = 0; y <= PARCEL - size; ++y)
                {
                    if (not *p) goto none_left;
                    // is this space empty
                    for (u32 xx = x; xx != x + size; ++xx)
                        for (u32 yy = y; yy != y + size; ++yy)
                            if (box[xx][yy]) goto non_empty;
                    // empty space, place this packet
                    for (u32 xx = x; xx != x + size; ++xx)
                        for (u32 yy = y; yy != y + size; ++yy)
                            box[xx][yy] = true;
//                    printf("place %ux%u @ %u,%u\n", size, size, x, y);
//                    _print_parcel(box);
                    --(*p);
                    non_empty:;
                }
            none_left:;
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    static_assert(PARCEL >= MAX_PACKET, "PARCEL >= MAX_PACKET");
    u32 amts[MAX_PACKET];
    for (;;)
    {
        for (u32 *p = amts; p != amts + MAX_PACKET; ++p)
        {
            int r = scanf("%u", p);
            assert(r == 1);
        }
        if (zero(amts)) break;
//        printf("read:");
//        for (u32 *p = amts; p != amts + MAX_PACKET; ++p) printf(" %u", *p);
//        printf("\n");
        printf("%u\n", parcels(amts));
    }
    return 0;
}
