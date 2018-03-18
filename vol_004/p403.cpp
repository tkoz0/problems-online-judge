#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#define ENDL "------------------------------------------------------------"
#define PAGE_W 60
#define PAGE_H 60
#define C5_W 6
#define C5_H 5
// C1 = small font, C5 = big font

std::map<char, std::vector<const char*> > c5bitmap;

void bitmap_init() // hardcoded bitmap data
{
    c5bitmap['A'] =
    {
        ".***..",
        "*...*.",
        "*****.",
        "*...*.",
        "*...*."
    };
    c5bitmap['B'] =
    {
        "****..",
        "*...*.",
        "****..",
        "*...*.",
        "****.."
    };
    c5bitmap['C'] =
    {
        ".****.",
        "*...*.",
        "*.....",
        "*.....",
        ".****."
    };
    c5bitmap['D'] =
    {
        "****..",
        "*...*.",
        "*...*.",
        "*...*.",
        "****.."
    };
    c5bitmap['E'] =
    {
        "*****.",
        "*.....",
        "***...",
        "*.....",
        "*****."
    };
    c5bitmap['F'] =
    {
        "*****.",
        "*.....",
        "***...",
        "*.....",
        "*....."
    };
    c5bitmap['G'] =
    {
        ".****.",
        "*.....",
        "*..**.",
        "*...*.",
        ".***.."
    };
    c5bitmap['H'] =
    {
        "*...*.",
        "*...*.",
        "*****.",
        "*...*.",
        "*...*."
    };
    c5bitmap['I'] =
    {
        "*****.",
        "..*...",
        "..*...",
        "..*...",
        "*****."
    };
    c5bitmap['J'] =
    {
        "..***.",
        "...*..",
        "...*..",
        "*..*..",
        ".**..."
    };
    c5bitmap['K'] =
    {
        "*...*.",
        "*..*..",
        "***...",
        "*..*..",
        "*...*."
    };
    c5bitmap['L'] =
    {
        "*.....",
        "*.....",
        "*.....",
        "*.....",
        "*****."
    };
    c5bitmap['M'] =
    {
        "*...*.",
        "**.**.",
        "*.*.*.",
        "*...*.",
        "*...*."
    };
    c5bitmap['N'] =
    {
        "*...*.",
        "**..*.",
        "*.*.*.",
        "*..**.",
        "*...*."
    };
    c5bitmap['O'] =
    {
        ".***..",
        "*...*.",
        "*...*.",
        "*...*.",
        ".***.."
    };
    c5bitmap['P'] =
    {
        "****..",
        "*...*.",
        "****..",
        "*.....",
        "*....."
    };
    c5bitmap['Q'] =
    {
        ".***..",
        "*...*.",
        "*...*.",
        "*..**.",
        ".****."
    };
    c5bitmap['R'] =
    {
        "****..",
        "*...*.",
        "****..",
        "*..*..",
        "*...*."
    };
    c5bitmap['S'] =
    {
        ".****.",
        "*.....",
        ".***..",
        "....*.",
        "****.."
    };
    c5bitmap['T'] =
    {
        "*****.",
        "*.*.*.",
        "..*...",
        "..*...",
        ".***.."
    };
    c5bitmap['U'] =
    {
        "*...*.",
        "*...*.",
        "*...*.",
        "*...*.",
        ".***.."
    };
    c5bitmap['V'] =
    {
        "*...*.",
        "*...*.",
        ".*.*..",
        ".*.*..",
        "..*..."
    };
    c5bitmap['W'] =
    {
        "*...*.",
        "*...*.",
        "*.*.*.",
        "**.**.",
        "*...*."
    };
    c5bitmap['X'] =
    {
        "*...*.",
        ".*.*..",
        "..*...",
        ".*.*..",
        "*...*."
    };
    c5bitmap['Y'] =
    {
        "*...*.",
        ".*.*..",
        "..*...",
        "..*...",
        "..*..."
    };
    c5bitmap['Z'] =
    {
        "*****.",
        "...*..",
        "..*...",
        ".*....",
        "*****."
    };
    c5bitmap[' '] =
    {
        "......",
        "......",
        "......",
        "......",
        "......"
    };
}

bool _debug_valid_char(char c) // small function for assertions
{
    return c == ' ' or ('A' <= c and c <= 'Z');
}

void flush_page(char **page) // fill with .
{
    for (char **r = page; r != page + PAGE_H; ++r)
    {
        char *c = *r;
        for (; c != *r + PAGE_W; ++c)
            *c = '.';
        *c = '\0';
    }
}

int main(int argc, char **argv)
{
    bitmap_init();
    // alloc memory for page
    char **page = (char**) malloc(PAGE_H * sizeof(char*));
    for (char **r = page; r != page + PAGE_H; ++r)
        *r = (char*) malloc((PAGE_W+1) * sizeof(char)); // +1 for null termination
    flush_page(page);
    std::string cmd, font;
    while (std::cin >> cmd)
    {
        if (cmd == ".EOP") // print contents and clear page
        {
            for (char **r = page; r != page + PAGE_H; ++r)
                printf("%s\n", *r);
            printf("\n%s\n\n", ENDL);
            flush_page(page);
            continue;
        }
        // next block, all cmds take font as 2nd argument (C1 or C5)
        std::cin >> font;
        bool c1 = false;
        if (font == "C1") c1 = true;
        else assert(font == "C5");
        u32 R, C;
        int r;
        if (cmd == ".P") // place (at coordinate)
        {
            r = scanf("%u %u", &R, &C);
            assert(r == 2);
            continue;
        }
        // next block, all cmds take row only
        r = scanf("%u", &R);
        assert(r == 1);
        if (cmd == ".L") // left justify (row)
        {
            ;
        }
        else if (cmd == ".R") // right justify (row)
        {
            ;
        }
        else if (cmd == ".C") // center (row), to right if odd string length
        {
            ;
        }
        else assert(0); // invalid command
    }
    // clear memory
    for (char **r = page; r != page + PAGE_H; ++r)
        free(*r);
    free(page);
    return 0;
}
