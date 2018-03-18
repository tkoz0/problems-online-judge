#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#define ENDL "------------------------------------------------------------"
#define PAGE_W 60
#define PAGE_H 60
#define C5_W 6
#define C5_H 5
#define BMPFILL '*'
#define BMPEMPTY '.'
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
// assume R,C are given in terms of counting starting from 0

// place small text at R,C
void c1p(char **page, u32 R, u32 C, char *text)
{
    char *chr = &(page[R][C]); // starting position
    while (C++ < PAGE_W and *text) // place chars while in range and nonnull
    {
        assert(_debug_valid_char(*text));
        if (*text != ' ') // blanks dont overwrite
            *chr = *text;
        ++text, ++chr;
    }
}

// small text at R,0
void c1l(char **page, u32 R, char *text)
{
    c1p(page, R, 0, text);
}

// small text, right end at R,(width-1)
void c1r(char **page, u32 R, char *text)
{
    char *chr = &(page[R][PAGE_W]); // start 1 past last on page row
    u32 C = PAGE_W;
    char *textp = text;
    while (*textp) // move to end of string
    {
        assert(_debug_valid_char(*textp));
        ++textp;
    }
    while (C-- and textp-- != text) // in range, not past beginning of text
    {
        --chr;
        if (*textp != ' ')
            *chr = *textp;
    }
}

// center aligns text on row R, for the odd-even lengths mismatch case:
// dealing with off-by-1 is configured for the provided specification
void c1c(char **page, u32 R, char *text)
{
    size_t textl = strlen(text);
    u32 Cmid = PAGE_W >> 1;
    char *textmidp = &(text[textl >> 1]); // midpoints calculated with indexes
    char *pagemidp = &(page[R][Cmid]);
    u32 C = Cmid;
    char *textp = textmidp, *pagep = pagemidp;
    while (C++ < PAGE_W and *textp) // write text past midpoint (and including)
    {
        assert(_debug_valid_char(*textp));
        if (*textp != ' ')
            *pagep = *textp;
        ++pagep, ++textp;
    }
    C = Cmid, textp = textmidp, pagep = pagemidp;
    while (C-- and textp-- != text) // write text before midpoint
    {
        assert(_debug_valid_char(*textp));
        --pagep;
        if (*textp != ' ')
            *pagep = *textp;
    }
}

// place big text at R,C (top left corner)
void c5p(char **page, u32 R, u32 C, char *text)
{
    u32 c5i = 0; // row index of the big text
    // main loop, skip rows that are cut off
    for (u32 row = R; row < PAGE_H and row < R + C5_H; ++row, ++c5i)
    {
        char *textp = text;
        char *pagep = &(page[row][C]);
        u32 col = C; // keep track of column to avoid going past page edge
        while (col < PAGE_W and *textp) // char loop: col in range, nonnull char
        {
            assert(_debug_valid_char(*textp));
            const char *bmp = c5bitmap[*textp][c5i]; // get bmp data ptr
            while (col < PAGE_W and *bmp) // bitmap loop
            {
                ++col; // increment after in came reaching null char in bmp line
                if (*bmp == BMPFILL)
                    *pagep = BMPFILL;
                else assert(*bmp == BMPEMPTY);
                ++pagep, ++bmp;
            }
            ++textp;
        }
    }
}

// place big text at R,1 (or R,0)
void c5l(char **page, u32 R, char *text)
{
    c5p(page, R, 0, text);
}

// similar to left justify but place the big test starting from right
void c5r(char **page, u32 R, char *text)
{
    u32 c5i = 0;
    for (u32 row = R; row < PAGE_H and row < R + C5_H; ++row, ++c5i)
    {
        char *textp = text;
        while (*textp) ++textp; // start at end of text
        char *pagep = &(page[row][PAGE_W]);
        u32 C = PAGE_W;
        while (C and textp-- != text)
        {
            assert(_debug_valid_char(*textp));
            const char *bmp = c5bitmap[*textp][c5i];
            while (*bmp) ++bmp; // find end
            while (C-- and bmp-- != c5bitmap[*textp][c5i])
            {
                --pagep;
                if (*bmp == BMPFILL)
                    *pagep = BMPFILL;
                else assert(*bmp == BMPEMPTY);
            }
        }
    }
}

// center big text
void c5c(char **page, u32 R, char *text)
{
    size_t textl = C5_W * strlen(text);
    u32 c5i = 0, Cmid = PAGE_W >> 1;
    for (u32 row = R; row < PAGE_H and row < R + C5_H; ++row, ++c5i)
    {
        char *pagep = &(page[row][Cmid]);
        u32 C = Cmid, c5texti = textl >> 1;
        while (C++ < PAGE_W and c5texti < textl) // print right half
        {
            assert(_debug_valid_char(text[c5texti / C5_W]));
            if (c5bitmap[text[c5texti / C5_W]][c5i][c5texti % C5_W] == BMPFILL)
                *pagep = BMPFILL;
            else assert(c5bitmap[text[c5texti / C5_W]][c5i][c5texti % C5_W]
                    == BMPEMPTY);
            ++pagep, ++c5texti;
        }
        C = Cmid, c5texti = textl >> 1, pagep = &(page[row][Cmid]);
        while (C-- and c5texti--)
        {
            assert(_debug_valid_char(text[c5texti / C5_W]));
            --pagep;
            if (c5bitmap[text[c5texti / C5_W]][c5i][c5texti % C5_W] == BMPFILL)
                *pagep = BMPFILL;
            else assert(c5bitmap[text[c5texti / C5_W]][c5i][c5texti % C5_W]
                    == BMPEMPTY);
        }
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
        int r; // return value of scanf for assertions
        if (cmd == ".P") // read R or (R and C) depending on command
        {
            r = scanf("%u %u", &R, &C);
            assert(r == 2);
        }
        else
        {
            r = scanf("%u", &R);
            C = 1; // dummy value to prevent assertion failure later
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
        --R, --C; // convert from provided 1..N to 0..N-1 numbering
        assert(R < PAGE_H);
        assert(C < PAGE_W);
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
