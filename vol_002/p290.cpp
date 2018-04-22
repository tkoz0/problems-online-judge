#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
typedef uint32_t u32;
#include <vector>
#define MAX_BASE 15
#define MAX_STEPS 100

inline bool is_palindrome(std::vector<u32>& num) // reads same both ways
{
    auto i1 = num.begin(), i2 = num.end();
    --i2;
    for (; i1 < i2; ++i1, --i2)
        if (*i1 != *i2) return false;
    return true;
}

// in place addition, adds n2 to n1
inline void add_nums(std::vector<u32>& n1, std::vector<u32>& n2, u32 base)
{
    auto i1 = n1.begin(), i2 = n2.begin();
    bool carry = false;
    for (; i1 != n1.end(); ++i1, ++i2)
    {
        if (carry)
        {
            ++(*i1);
            carry = false;
        }
        *i1 += *i2;
        if (*i1 >= base)
        {
            *i1 -= base;
            carry = true;
        }
    }
    if (carry) n1.push_back(1);
}

// number is a digit vector, little endian
inline u32 palindrome_steps(std::vector<u32> num1, u32 base)
{
    u32 steps = 0;
    assert(2 <= base and base <= MAX_BASE);
    for (u32 n : num1) if (n >= base) return -1; // not valid in base
    std::vector<u32> num2;
    for (;; ++steps)
    {
        assert(steps <= MAX_STEPS);
        if (is_palindrome(num1)) return steps;
        for (auto itr = num1.end(); itr-- != num1.begin();)
            num2.push_back(*itr);
        add_nums(num1, num2, base);
        num2.clear();
    }
}

int main(int argc, char **argv)
{
    char c;
    std::vector<u32> num;
    while (scanf("%c", &c) == 1)
    {
        do // read digits until end of line
        {
            if ('0' <= c and c <= '9') num.push_back(u32(c - '0'));
            else if ('A' <= c and c <= 'E') num.push_back(u32(10 + c - 'A'));
            else assert(0);
            int r = scanf("%c", &c);
            assert(r == 1);
        }
        while (c != '\n');
        // perform reverse-and-add process on different bases
        for (u32 b = MAX_BASE; b != 1; --b)
        {
            u32 steps = palindrome_steps(num, b);
            if (b == 2)
            {
                if (steps == -1) printf("?\n");
                else printf("%u\n", steps);
            }
            else
            {
                if (steps == -1) printf("? ");
                else printf("%u ", steps);
            }
        }
        num.clear();
    }
    return 0;
}
