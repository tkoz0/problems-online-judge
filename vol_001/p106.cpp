#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <set>
#include <algorithm>

typedef uint32_t u32;
#define MAX_N 1000000

struct triple // class to store some triple with a < b < c
{
    u32 a, b, c;
    triple(u32 a, u32 b, u32 c)
    {
        assert(a < b and b < c);
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

bool operator<(const triple& x, const triple& y)
{
    if (x.c != y.c) return x.c < y.c;
    if (x.a != y.a) return x.a < y.a;
    return x.b < y.b;
}

u32 gcd(u32 x, u32 y)
{
    assert(x > y);
    while (y)
    {
        u32 t = y;
        y = x % y;
        x = t;
    }
    return x;
}

std::set<triple> gen_primitives(u32 limit)
{
    std::set<triple> triples;
    // generate with a = m^2 - n^2, b = 2mn, c = m^2 + n^2
    // gcd(m,n)=1, m > n, both have different parity (odd/even)
    u32 m, n, mm, nn, a, b, c;
    for (m = 2; (mm = (m * m)) < limit; ++m) // ensure c < limit
    {
        for (n = (m & 1) ? 2 : 1; m > n and (mm + (nn = (n * n))) <= limit;
            n += 2)
        {
            if (gcd(m, n) != 1) continue;
            a = mm - nn;
            b = (m * n) << 1;
            c = mm + nn;
            if (a > b) std::swap(a, b); // make sure order is right (a<b<c)
            triples.insert(triple(a, b, c));
        }
    }
    return triples;
}

void _debug_print(std::set<triple>& primitives)
{
    for (auto t : primitives)
        printf("%02u %02u %02u\n", t.a, t.b, t.c);
}

int main(int argc, char **argv)
{
    u32 N;
    std::set<triple> primitives = gen_primitives(MAX_N);
//    printf("_debug: generated %lu triples\n", primitives.size());
//    _debug_print(primitives);
    while (scanf("%u\n", &N) == 1)
    {
        assert(N and N <= MAX_N);
        // first result is num coprime triples with all components <= N
        // second result is how many nums <= N are not part of any triple
        u32 prim_ct = 0; // count primitives
        auto itr = primitives.begin();
        for (; itr != primitives.end(); ++itr, ++prim_ct)
            if (itr->c > N) break;
        // prim_ct now counts primitive triples, itr points to 1 beyond last
        bool *nums = (bool*) calloc(N + 1, sizeof(bool));
        assert(nums);
        for (auto itr2 = primitives.begin(); itr2 != itr; ++itr2)
        {
            u32 a = itr2->a, b = itr2->b, c = itr2->c;
            while (c <= N)
            {
                nums[a] = nums[b] = nums[c] = true; // set as found
                a += itr2->a, b += itr2->b, c += itr2->c; // next multiple
            }
        }
        // count how many were not used in triples
        u32 not_ct = 0; // how many not in triples
        for (bool *b = nums + 1; b <= nums + N; ++b)
            if (not *b) ++not_ct;
        printf("%u %u\n", prim_ct, not_ct);
        free(nums);
    }
    return 0;
}
