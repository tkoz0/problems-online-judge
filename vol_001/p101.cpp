#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include <list>

typedef uint32_t u32;

struct block_world
{
    u32 _num_blocks;
    std::list<u32> *_piles;
    block_world(u32 num_blocks)
    {
        assert(num_blocks > 0 and num_blocks < 25);
        this->_num_blocks = num_blocks;
        this->_piles = new std::list<u32>[this->_num_blocks];
    }
    ~block_world() { delete[] this->_piles; }
    void print_world() const
    {
        // for each pile
        for (u32 i = 0; i < this->_num_blocks; ++i)
        {
            printf("%u:", i);
            for (auto itr = this->_piles[i].cbegin();
                    itr != this->_piles[i].cend(); ++itr)
                printf(" %u", *itr);
            printf("\n");
        }
    }
    // locate a block, O(n) time, return pile index and iterator to the block
    std::pair<u32, std::list<u32>::const_iterator> _find_block(u32 block) const
    {
        assert(block < this->_num_blocks);
        for (u32 i = 0; i < this->_num_blocks; ++i)
        {
            for (auto itr = this->_piles[i].cbegin();
                    itr != this->_piles[i].cend(); ++itr)
                // found block
                if (*itr == block)
                    return std::make_pair(i, itr);
        }
        assert(0); // should never reach here
    }
    // blocks above are moved to original positions
    void _above_to_original(std::pair<u32, std::list<u32>::const_iterator> loc)
    {
        assert(loc.first < this->_num_blocks);
        assert(loc.second != this->_piles[loc.first].end());
        ++loc.second;
        while (loc.second != this->_piles[loc.first].end())
        {
            assert(*loc.second < this->_num_blocks);
            this->_piles[*loc.second].push_back(*loc.second);
            loc.second = this->_piles[loc.first].erase(loc.second);
        }
    }
    void move_onto(u32 a, u32 b)
    {
        printf("not implemented\n");
    }
    void move_over(u32 a, u32 b)
    {
        printf("not implemented\n");
    }
    void pile_onto(u32 a, u32 b)
    {
        printf("not implemented\n");
    }
    void pile_over(u32 a, u32 b)
    {
        printf("not implemented\n");
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
    }
    assert(strcmp(w1, "quit") == 0);
}
