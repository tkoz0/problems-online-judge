#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include <list>

typedef uint32_t u32;
#define MOST_BLOCKS 25

struct block_world
{
    // typedef for block position, a list iterator
    typedef std::pair<u32, std::list<u32>::const_iterator> blockpos;
    u32 _num_blocks;
    std::list<u32> *_piles;
    block_world(u32 num_blocks)
    {
        assert(num_blocks > 0 and num_blocks < MOST_BLOCKS);
        this->_num_blocks = num_blocks;
        // the choice to use std::list is because multiple blocks will be moved
        // for some commands, this can be done efficiently with splicing
        this->_piles = new std::list<u32>[this->_num_blocks];
        // insert blocks into initial locations
        for (u32 i = 0; i != this->_num_blocks; ++i)
            this->_piles[i].push_back(i);
    }
    ~block_world() { delete[] this->_piles; }
    void print_world() const
    {
        // for each pile
        for (u32 i = 0; i != this->_num_blocks; ++i)
        {
            printf("%u:", i);
            for (auto itr = this->_piles[i].cbegin();
                    itr != this->_piles[i].cend(); ++itr)
                printf(" %u", *itr);
            printf("\n");
        }
    }
    // locate a block, O(n) time, return pile index and iterator to the block
    blockpos _find_block(u32 block) const
    {
        assert(block < this->_num_blocks);
        // search each pile
        for (u32 i = 0; i < this->_num_blocks; ++i)
        {
            // find block in pile
            for (auto itr = this->_piles[i].cbegin();
                    itr != this->_piles[i].cend(); ++itr)
                // found block
                if (*itr == block)
                    return std::make_pair(i, itr);
        }
        assert(0); // should never reach here
    }
    // blocks above are moved to original positions
    void _above_to_original(blockpos loc)
    {
        assert(loc.first < this->_num_blocks);
        assert(loc.second != this->_piles[loc.first].end());
        ++loc.second;
        // remove blocks from pile and return to original locations
        while (loc.second != this->_piles[loc.first].end())
        {
            assert(*loc.second < this->_num_blocks);
            this->_piles[*loc.second].push_back(*loc.second);
            loc.second = this->_piles[loc.first].erase(loc.second);
        }
    }
    // returns true if a and b are in different piles
    // sets 2 block positions (of a and b)
    bool _dif_piles(u32 a, u32 b, blockpos *posa, blockpos *posb) const
    {
        assert(a < this->_num_blocks and b < this->_num_blocks);
        // operation invalid if blocks are in the same pile
        if (a == b) return false;
        blockpos bpa = this->_find_block(a);
        blockpos bpb = this->_find_block(b);
        if (bpa.first == bpb.first) return false;
        *posa = bpa;
        *posb = bpb;
        return true;
    }
    // return blocks above a and b to original positions, then move a onto b
    void move_onto(u32 a, u32 b)
    {
        blockpos bpa, bpb;
        if (!this->_dif_piles(a, b, &bpa, &bpb)) return;
        this->_above_to_original(bpa);
        this->_above_to_original(bpb);
        this->_piles[bpb.first].push_back(*bpa.second);
        this->_piles[bpa.first].pop_back(); // block a is at top of pile
    }
    // return blocks above a to original positions, then move a over b
    void move_over(u32 a, u32 b)
    {
        blockpos bpa, bpb;
        if (!this->_dif_piles(a, b, &bpa, &bpb)) return;
        this->_above_to_original(bpa);
        this->_piles[bpb.first].push_back(*bpa.second);
        this->_piles[bpa.first].pop_back();
    }
    // blocks above b to original, a and blocks above it onto pile b
    void pile_onto(u32 a, u32 b)
    {
        blockpos bpa, bpb;
        if (!this->_dif_piles(a, b, &bpa, &bpb)) return;
        this->_above_to_original(bpb);
        while (bpa.second != this->_piles[bpa.first].end())
        {
            this->_piles[bpb.first].push_back(*bpa.second);
            bpa.second = this->_piles[bpa.first].erase(bpa.second);
        }
    }
    // a and blocks above it over pile b
    void pile_over(u32 a, u32 b)
    {
        blockpos bpa, bpb;
        if (!this->_dif_piles(a, b, &bpa, &bpb)) return;
        while (bpa.second != this->_piles[bpa.first].end())
        {
            this->_piles[bpb.first].push_back(*bpa.second);
            bpa.second = this->_piles[bpa.first].erase(bpa.second);
        }
    }
};

int main(int argc, char **argv)
{
    u32 num_blocks;
    scanf("%u", &num_blocks);

    // setup block world
    block_world bw(num_blocks);

    // process commands
    char w1[5], w2[5];
    u32 i1, i2;
    // format is 2 4char strings and 2 unsigned integers
    while (scanf("%4s %u %4s %u", w1, &i1, w2, &i2) == 4)
    {
        assert(i1 < num_blocks and i2 < num_blocks);
        if (strcmp(w1, "move") == 0)
        {
            if (strcmp(w2, "onto") == 0)
            {
                bw.move_onto(i1, i2);
            }
            else
            {
                assert(strcmp(w2, "over") == 0);
                bw.move_over(i1, i2);
            }
        }
        else
        {
            assert(strcmp(w1, "pile") == 0);
            if (strcmp(w2, "onto") == 0)
            {
                bw.pile_onto(i1, i2);
            }
            else
            {
                assert(strcmp(w2, "over") == 0);
                bw.pile_over(i1, i2);
            }
        }
        static int tmp = 0;
//        printf("\nstep %u: %4s %u %4s %u\n",++tmp,w1,i1,w2,i2);
//        bw.print_world();
    }
    assert(strcmp(w1, "quit") == 0);
    bw.print_world();
    return 0;
}
