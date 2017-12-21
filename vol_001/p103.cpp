#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include <algorithm>

typedef uint32_t u32;
#define MAX_BOXES 30
#define MAX_DIMS 10

struct box_set
{
    // d and n for current number of dimensions and boxes respectively
    u32 _max_dims, _max_boxes, _d, _n;
    u32 **_boxes;
    box_set(u32 max_boxes, u32 max_dims)
    {
        this->_max_boxes = max_boxes;
        this->_max_dims = max_dims;
        this->_d = this->_n = 0;
        this->_boxes = nullptr;
    }
    ~box_set()
    {
        if (!this->_boxes) return;
        // iterate all dynamic memory and free it
        for (u32 **p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
            free(*p);
        free(this->_boxes);
    }
};

int main(int argc, char **argv)
{
    u32 num, dim;
    box_set bs(MAX_BOXES, MAX_DIMS);
    while (scanf("%u %u", &num, &dim) == 2)
    {
        // num lines, each line has dim integers representing a box
        // problem specifies that there will be 1-10 dims and up to 30 boxes
        assert(1 <= dim and dim <= 10);
        assert(num <= 30);
    }
    return 0;
}
