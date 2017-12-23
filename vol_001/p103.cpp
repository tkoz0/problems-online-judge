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
    struct box { u32 num; u32 *dims; };
    u32 _max_dims, _max_boxes, _d, _n;
    box *_boxes;
    bool **_nest;
    box_set(u32 max_boxes, u32 max_dims)
    {
        this->_max_boxes = max_boxes;
        this->_max_dims = max_dims;
        this->_d = this->_n = 0;
        // allocate most space needed for box storage
        this->_boxes = (box*) malloc(this->_max_boxes * sizeof(box));
        u32 box_i = 1;
        // for each box, set box id and allocate space for dimension lengths
        for (box *p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
        {
            p->num = box_i++;
            p->dims = (u32*) malloc(this->_max_dims * sizeof(u32));
        }
        // generate uninitialized nesting table
        this->_nest = (bool**) malloc(this->_max_boxes * sizeof(bool*));
        for (bool **b = this->_nest; b != this->_nest + this->_max_boxes; ++b)
            *b = (bool*) malloc(this->_max_boxes * sizeof(bool));
    }
    ~box_set()
    {
        for (box *p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
            free(p->dims);
        free(this->_boxes);
        for (bool **b = this->_nest; b != this->_nest + this->_max_boxes; ++b)
            free(*b);
        free(b);
    }
    // returns true if another set of boxes is read successfully from stdin
    // no memory reallocation, overwrites with new box data
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
        for (box *b = this->_boxes; b != this->_boxes + this->_n; ++b)
            for (u32 *d = b->dims; d != b->dims + this->_d; ++d)
                if (!scanf("%u", d)) return false;
        return true;
    }
    void _debug_print_boxes() const
    {
        for (box *b = this->_boxes; b != this->_boxes + this->_n; ++b)
        {
            printf("box %02u:", b->num);
            for (u32 *d = b->dims; d != b->dims + this->_d; ++d)
                printf(" %u", *d);
            printf("\n");
        }
    }
    // comparison function for qsort, 2 integers
    // this should work if *x and *y are in range 0 to 2^31-1, <0 = x before y
    static inline int _cmp_u32(const void *x, const void *y)
    {
        return *((const int32_t*) x) - *((const int32_t*) y);
    }
    // comparing the u32* arrays from 2 boxes, sort by 1st dim, 2nd, etc
    // this static variable is to "hack" a 3rd argument (length of dimensions)
    static u32 __cmp_dims;
    static inline int _cmp_box(const void *x, const void *y)
    {
        const u32 *end = ((const box*) x)->dims + box_set::__cmp_dims;
        const u32 *xx = ((const box*) x)->dims, *yy = ((const box*) y)->dims;
        for (; xx != end; ++xx, ++yy)
            if (*xx != *yy)
                return (int32_t) (*xx - *yy);
        return 0; // equivalent if all dimensions equal
    }
    // takes O(n*d*logd) time for 1st step and O(n*logn) for 2nd step
    void sort_boxes()
    {
        // first sort dimensions within each box
        for (box *b = this->_boxes; b != this->_boxes + this->_n; ++b)
            qsort(b->dims, this->_d, sizeof(u32), &this->_cmp_u32);
        // store 3rd argument and sort boxes
        box_set::__cmp_dims = this->_d;
        qsort(this->_boxes, this->_n, sizeof(box_set::box), &this->_cmp_box);
    }
    inline bool _fits_in(box *a, box *b) const
    {
        u32 *end = a->dims + this->_d;
        u32 *aa = a->dims, *bb = b->dims;
        // if dimensions of a and b are sorted, a does not fit in b if there is
        // a pair of corresponding dimensions a_i and b_i such that a_i >= b_i
        for (; aa != end; ++aa, ++bb)
            if (*aa >= *bb)
                return false;
        return true;
    }
    // generate the table to determine if boxes nest within each other
    // uses box indexes (after sorting)
    void gen_nest_table()
    {
        box *ba = this->_boxes;
        bool **na = this->_nest;
        // loop over 1st box and nest table row
        for (; ba != this->_boxes + this->_n; ++ba, ++na)
        {
            box *bb = this->_boxes;
            bool *nb = *na;
            // loop over 2nd box and nest table column in this nest table row
            for (; bb != this->_boxes + this->_n; ++bb, ++nb)
                *nb = this->_fits_in(ba, bb);
        }
    }
};

// static member var to "hack" qsort to allow a 3rd argument in comparison
u32 box_set::__cmp_dims = 0;

int main(int argc, char **argv)
{
    box_set bs(MAX_BOXES, MAX_DIMS);
    while (bs.read_boxes())
    {
        bs._debug_print_boxes();
        bs.sort_boxes();
        bs.gen_nest_table();
        bs._debug_print_boxes();
    }
    return 0;
}
