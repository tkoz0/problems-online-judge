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
#define MAXSTRLEN 60
typedef uint32_t u32;
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

// functions to process print commands, named as <font><cmd>

void c1p(char **page, u32 R, u32 C, char *text){}
void c1l(char **page, u32 R, char *text){}
void c1r(char **page, u32 R, char *text){}
void c1c(char **page, u32 R, char *text){}
void c5p(char **page, u32 R, u32 C, char *text){}
void c5l(char **page, u32 R, char *text){}
void c5r(char **page, u32 R, char *text){}
void c5c(char **page, u32 R, char *text){}

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
        if (cmd == ".P") // read R or (R and C) depending on command
        {
            r = scanf("%u %u", &R, &C);
            assert(r == 2);
        }
        else
        {
            r = scanf("%u", &R);
            assert(r == 1);
        }
        // next read string data and null terminate it
        char text[MAXSTRLEN+1], c;
        u32 texti = 0;
        for (;;) // read up to and skip first |
        {
            r = scanf("%c", &c);
            assert(r == 1);
            if (c == '|') break; // begins string
        }
        for (;;)
        {
            r = scanf("%c", &c);
            assert(r == 1);
            if (c == '|') break; // terminates string
            text[texti++] = c;
            assert(texti <= MAXSTRLEN); // cannot exceed longest allowed string
        }
        text[texti] = '\0';
        // finally process the command
        if (cmd == ".P") // place (row, column)
        {
            if (c1) c1p(page, R, C, text);
            else c5p(page, R, C, text);
        }
        else if (cmd == ".L") // left justify (row)
        {
            if (c1) c1l(page, R, text);
            else c5l(page, R, text);
        }
        else if (cmd == ".R") // right justify (row)
        {
            if (c1) c1r(page, R, text);
            else c5r(page, R, text);
        }
        else if (cmd == ".C") // center (row), to right if odd string length
        {
            if (c1) c1c(page, R, text);
            else c5c(page, R, text);
        }
        else assert(0); // invalid command
    }
    // clear memory
    for (char **r = page; r != page + PAGE_H; ++r)
        free(*r);
    free(page);
    return 0;
}