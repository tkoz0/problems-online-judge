#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <map>
typedef uint32_t u32;

struct half
{
    std::map<u32,u32> _nums; // map unique integers to how many instances
    u32 _size;
    half() { _size = 0; }
    void insert(u32 n)
    {
        auto itr = _nums.find(n);
        if (itr == _nums.end()) _nums[n] = 1;
        else ++(itr->second);
        ++_size;
    }
    u32 size() const { return _size; }
    u32 max() const
    {
        auto itr = _nums.crbegin();
        assert(itr != _nums.crend());
        return itr->first;
    }
    u32 min() const
    {
        auto itr = _nums.cbegin();
        assert(itr != _nums.cend());
        return itr->first;
    }
    u32 pop_max()
    {
        auto itr = _nums.rbegin();
        assert(itr != _nums.rend());
        --_size;
        if (itr->second == 1)
        {
            u32 val = itr->first;
            _nums.erase(itr->first);
            return val;
        }
        else
        {
            --(itr->second);
            return itr->first;
        }
    }
    u32 pop_min()
    {
        auto itr = _nums.begin();
        assert(itr != _nums.end());
        --_size;
        if (itr->second == 1)
        {
            u32 val = itr->first;
            _nums.erase(itr->first);
            return val;
        }
        else
        {
            --(itr->second);
            return itr->first;
        }
    }
};

void _debug_show_halves(half left, bool has_middle, u32 middle, half right)
{
    for (auto n : left._nums)
        for (u32 i = 0; i < n.second; ++i)
            printf("%u ",n.first);
    printf("| ");
    if (has_middle) printf("%u | ",middle);
    for (auto n : right._nums)
        for (u32 i = 0; i < n.second; ++i)
            printf("%u ",n.first);
    printf("\n");
}

int main(int argc, char **argv)
{
    half left, right; // divide the list into sorted halves
    bool has_middle = false;
    u32 middle, X;
    // special exception for first number
    int r = scanf("%u",&X);
    assert(r == 1);
    middle = X;
    has_middle = true;
    printf("%u\n",X);
    while (scanf("%u",&X) == 1)
    {
        assert(X < (1 << 31));
        assert(left.size() == right.size());
        if (has_middle)
        {
            if (X < middle)
            {
                left.insert(X);
                right.insert(middle);
            }
            else if (X > middle)
            {
                right.insert(X);
                left.insert(middle);
            }
            else
            {
                left.insert(X);
                right.insert(X);
            }
            has_middle = false;
            printf("%u\n",(left.max()+right.min())/2);
        }
        else // both left and right will have at least 1 element
        {
            u32 lmax = left.max(), rmin = right.min();
            if (X < lmax)
            {
                left.insert(X);
                middle = left.pop_max();
            }
            else if (X > rmin)
            {
                right.insert(X);
                middle = right.pop_min();
            }
            else middle = X;
            has_middle = true;
            printf("%u\n",middle);
        }
//        _debug_show_halves(left,has_middle,middle,right);
    }
    return 0;
}
