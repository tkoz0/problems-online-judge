#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

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
    // used for solutions
    u32 *_path;
    u32 *_lpath;
    u32 _longest;
    box_set(u32 max_boxes, u32 max_dims)
    {
        this->_max_boxes = max_boxes;
        this->_max_dims = max_dims;
        this->_d = this->_n = 0;
        // allocate most space needed for box storage
        this->_boxes = (box*) malloc(this->_max_boxes * sizeof(box));
        // for each box, set box id and allocate space for dimension lengths
        for (box *p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
            p->dims = (u32*) malloc(this->_max_dims * sizeof(u32));
        // box->num left uninitialized, to be initialized by read_boxes()
        // generate uninitialized nesting table
        this->_nest = (bool**) malloc(this->_max_boxes * sizeof(bool*));
        for (bool **b = this->_nest; b != this->_nest + this->_max_boxes; ++b)
            *b = (bool*) malloc(this->_max_boxes * sizeof(bool));
        // allocate memory for recursive solution
        this->_path = (u32*) malloc(this->_max_boxes * sizeof(u32));
        this->_lpath = (u32*) malloc(this->_max_boxes * sizeof(u32));
    }
    ~box_set()
    {
        for (box *p = this->_boxes; p != this->_boxes + this->_max_boxes; ++p)
            free(p->dims);
        free(this->_boxes);
        for (bool **b = this->_nest; b != this->_nest + this->_max_boxes; ++b)
            free(*b);
        free(this->_nest);
        free(this->_path);
        free(this->_lpath);
    }
    // returns true if another set of boxes is read successfully from stdin
    // no memory reallocation, overwrites with new box data
    // number of boxes and dims in this set stored, extra data is "garbage"
    bool read_boxes()
    {
        u32 num, dim, box_num = 0;
        // first line has num boxes and num dimensions
        if (scanf("%u %u", &num, &dim) != 2) return false;
        // problem detail specifies there will be 1-10 dims and 30 boxes max
        assert(1 <= dim and dim <= this->_max_dims);
        assert(num <= this->_max_boxes);
        this->_n = num;
        this->_d = dim;
        // read 1 box per line
        for (box *b = this->_boxes; b != this->_boxes + this->_n; ++b)
        {
            b->num = ++box_num; // number identifying the box (1...n)
            for (u32 *d = b->dims; d != b->dims + this->_d; ++d)
                if (!scanf("%u", d)) return false;
        }
        return true;
    }
    void _debug_print_boxes(const char *str) const
    {
        printf("%s\n", str);
        for (box *b = this->_boxes; b != this->_boxes + this->_n; ++b)
        {
            printf("box %02u:", b->num);
            for (u32 *d = b->dims; d != b->dims + this->_d; ++d)
                printf(" %u", *d);
            printf("\n");
        }
    }
    // comparison function for qsort, 2 integers
    // <0=right order, >0=wrong order, 0=equivalent
    static inline int _cmp_u32(const void *x, const void *y)
    {
        if (*((const u32*) x) < *((const u32*) y)) return -1;
        if (*((const u32*) x) > *((const u32*) y)) return 1;
        return 0;
    }
    // comparing the u32* arrays from 2 boxes, sort by 1st dim, 2nd, etc
    // this static variable is to "hack" a 3rd argument (length of dimensions)
    static u32 __cmp_dims;
    static inline int _cmp_box(const void *x, const void *y)
    {
        const u32 *end = ((const box*) x)->dims + box_set::__cmp_dims;
        const u32 *xx = ((const box*) x)->dims, *yy = ((const box*) y)->dims;
        for (; xx != end; ++xx, ++yy)
            if (*xx != *yy) // ignore equivalent values
            {
                if (*xx < *yy) return -1;
                return 1;
                // similar to _cmp_u32
            }
        // if equivalent, use box ids
        // should not have to worry about box numbers being equal
        // qsort should not compare the same box to itself
        if (((const box*) x)->num < ((const box*) y)->num) return -1;
        return 1;
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
    // requires about O(n^2) time, O(d*n^2) at worst
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
    void _debug_print_nest_table(const char *str) const
    {
        printf("%s\n", str);
        for (bool **na = this->_nest; na != this->_nest + this->_n; ++na)
        {
            bool *nb = *na;
            for (; nb != *na + this->_n - 1; ++nb)
                printf("%i ", *nb);
            printf("%i\n", *nb);
        }
    }
    void _debug_print_path(u32 len) const
    {
        for (u32 *n = this->_path; n != this->_path + len; ++n)
            printf("%u ", *n);
        printf("\n");
    }
    // _path and _lpath for current and longest path found respectively
    // _longest saves length of longest found path
    // recurses through sorted data as a directed acyclic graph
    void _recurse(u32 pi)
    {
//        this->_debug_print_path(pi + 1);
        // current path length = pi + 1
        u32 needed;
        bool any_next = false; // if any further recursed paths
        if (pi + 1 >= this->_longest) needed = 0;
        else needed = this->_longest - pi;
        bool *nestp = this->_nest[this->_path[pi]];
        u32 next_bi = this->_path[pi] + 1; // next box
        nestp += next_bi; // boolean to determine nesting
        // loop while a longer path is possible
        for (; next_bi + needed < this->_n; ++next_bi, ++nestp)
        {
            if (!*nestp) continue;
            any_next = true;
            // store next box and recurse
            this->_path[pi + 1] = next_bi;
            this->_recurse(pi + 1);
        }
        if (any_next) return;
        if (pi >= this->_longest) // new longer path, copy
        {
            this->_longest = pi + 1;
            u32 *p = this->_path, *lp = this->_lpath;
            for (; p != this->_path + this->_longest; ++p, ++lp)
                *lp = *p;
            return;
        }
        if (pi + 1 == this->_longest) // equal length, use lexicographic order
        {
            u32 *p = this->_path, *lp = this->_lpath;
            for (; p != this->_path + this->_longest; ++p, ++lp)
            {
                if (*p == *lp) continue; // equal
                // this path comes after lexicographically
                if (this->_boxes[*p].num > this->_boxes[*lp].num) return;
                // copy path
                p = this->_path, lp = this->_lpath;
                for (; p != this->_path + this->_longest; ++p, ++lp)
                    *lp = *p;
                return;
            }
        }
    }
    void find_longest_recursive()
    {
        if (!this->_n) return; // do not attempt if box set is empty
        this->_longest = 0;
        *this->_path = 0;
        // avoid looping past the point where a longer sequence cant be found
        for (u32 start = 0; start + this->_longest <= this->_n;
                ++start, ++*this->_path)
            this->_recurse(0);
        assert(this->_longest); // path length should be at least 1 box
        printf("%u\n", this->_longest); // path len on line by itself
        u32 *p = this->_lpath;
        // print path, first separately to avoid extra space
        printf("%u", this->_boxes[*p].num);
        for (++p; p != this->_lpath + this->_longest; ++p)
            printf(" %u", this->_boxes[*p].num);
        printf("\n");
    }
    // lpath = longest that can be made, path = next one to create longest path
    // if path array has 0 then it means path is terminated
    void find_longest_dynamic()
    {
        u32 *p = this->_path + this->_n, *lp = this->_lpath + this->_n;
        bool **nr = this->_nest + this->_n; // row in nesting table
        box *b = this->_boxes + this->_n;
        --p, --lp, --nr, --b;
        *p = 0, *lp = 1; // initial, last box path length 1, no next box
        // p = next box of current, lp = max path len starting from current
        // b = current box, nr = nest table row for current box
        for (; p-- != this->_path;)
        {
            // out of possible next boxes current one fits into
            // choose smallest numbered box with max path length
            box *bb = b--;
            u32 *lpc = lp--; // longest path iterator
            *p = 0, *lp = 1; // initial conditions, if box cant nest in another
            bool *nbox = *(--nr) + (bb - this->_boxes);
//printf("ntablerow="); for (bool *bbb = nbox; bbb != *nr + this->_n; ++bbb) printf(" %u", *bbb); printf("\n");
            u32 bnum = 0;
            for (; bb != this->_boxes + this->_n; ++bb, ++nbox, ++lpc)
            {
                if (!*nbox) continue; // does not nest
                if (1 + *lpc > *lp or (1 + *lpc == *lp and bb->num < bnum))
                {
                    bnum = bb->num; // save box number
                    *p = bb - this->_boxes; // index of next box
                    *lp = 1 + *lpc; // length of path
                }
            }
        }
//printf("_path ="); for (u32 i = 0; i != this->_n; ++i) printf(" %u", _path[i]); printf("\n");
//printf("_lpath ="); for (u32 i = 0; i != this->_n; ++i) printf(" %u", _lpath[i]); printf("\n");
        // use p for start of path, lp as iterator over longest path
        p = this->_path;
        lp = this->_lpath;
        b = this->_boxes;
        u32 lplen = *(lp++);
        u32 bnum = (b++)->num;
        for (; lp != this->_lpath + this->_n; ++lp, ++b)
            if (*lp > lplen or (*lp == lplen and b->num < bnum))
            {
                lplen = *lp;
                bnum = b->num;
                p = this->_path + (b - this->_boxes); // set start point
            }
        // write output
        printf("%u\n%u", lplen, this->_boxes[p - this->_path].num);
        while (*p) // continue until reaching end zero
        {
            printf(" %u", this->_boxes[*p].num);
            p = this->_path + *p;
        }
        printf("\n");
    }
};

// static member var to "hack" qsort to allow a 3rd argument in comparison
u32 box_set::__cmp_dims = 0;

int main(int argc, char **argv)
{
    box_set bs(MAX_BOXES, MAX_DIMS);
    while (bs.read_boxes())
    {
//        bs._debug_print_boxes("initial");
        bs.sort_boxes();
        bs.gen_nest_table();
//        bs._debug_print_boxes("sorted");
//        bs._debug_print_nest_table("nest table");
//        bs.find_longest_recursive();
        bs.find_longest_dynamic();
    }
    return 0;
}
