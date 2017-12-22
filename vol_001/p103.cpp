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
        // allocate maximum space needed
        this->_boxes = (u32**) malloc(this->_max_boxes * sizeof(u32*));
        for (u32 **p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
            *p = (u32*) malloc(this->_max_dims * sizeof(u32));
    }
    ~box_set()
    {
        // iterate all dynamic memory and free it
        for (u32 **p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
            free(*p);
        free(this->_boxes);
    }
    // returns true if another set of boxes is read successfully from stdin
    // no memory reallocation, overwrites 2d array with box data
    // number of boxes and dims in this set stored, extra data is "garbage"
    bool read_boxes()
    {
        u32 num, dim;
        // first line has num boxes and num dimensions
        if (scanf("%u %u", &num, &dim) != 2) return false;
        // problem detail specifies there will be 1-10 dims and 30 boxes max
        assert(1 <= dim and dim <= this->_max_dims);
        assert(num <= this->_max_boxes);
        this->_n = num;
        this->_d = dim;
        // read 1 box per line
        for (u32 **b = this->_boxes; b != this->_boxes + this->_n; ++b)
            // read each dimension from this box
            for (u32 *d = *b; d != *b + this->_d; ++d)
                if (!scanf("%u", d)) return false;
        return true;
    }
    void _debug_print_boxes() const
    {
        for (u32 b = 0; b != this->_n; ++b)
        {
            printf("box %02u:", b + 1);
            for (u32 *d = this->_boxes[b]; d != this->_boxes[b] + this->_d; ++d)
                printf(" %u", *d);
            printf("\n");
        }
    }
    // requires O(n*d*logd + n*logn) time
    // should work fine if *x and *y are 31 bit (0 to 2^31-1)
    // <0 means x before y
    static inline int _cmp_u32(const void *x, const void *y)
    {
        return *((int32_t*) x) - *((int32_t*) y);
    }
    // compares 2 u32* arrays (2 boxes) to sort by 1st dim, then 2nd, etc
    // uses a static variable to allow a 3rd argument (length of arrays)
    static u32 __cmpdims;
    static inline int _cmp_u32p(const void *x, const void *y)
    {
        const u32 *end = *(const u32**) x + box_set::__cmpdims;
        const u32 *xx = *(const u32**) x, *yy = *(const u32**) y;
        for (; xx != end; ++xx, ++yy)
            if (*xx != *yy)
                return (int32_t) (*xx - *yy);
        return 0;
    }
    void sort_boxes()
    {
        // sort dimensions in each box
        for (u32 **b = this->_boxes; b != this->_boxes + this->_n; ++b)
            qsort(*b, this->_d, sizeof(**b), &this->_cmp_u32);
        // store 3rd argument in static variable, then sort boxes
        box_set::__cmpdims = this->_d;
        qsort(this->_boxes, this->_n,
                sizeof(*this->_boxes), &this->_cmp_u32p);
    }
};

// static member var to "hack" qsort to allow a 3rd argument in comparison
u32 box_set::__cmpdims = 0;

int main(int argc, char **argv)
{
    box_set bs(MAX_BOXES, MAX_DIMS);
    while (bs.read_boxes())
    {
        bs._debug_print_boxes();
        bs.sort_boxes();
        bs._debug_print_boxes();
    }
    return 0;
}
