#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_STR_LEN 20
#define NOT_PALIN " -- is not a palindrome."
#define REG_PALIN " -- is a regular palindrome."
#define MIR_STR " -- is a mirrored string."
#define MIR_PALIN " -- is a mirrored palindrome."

bool palin(char *w, size_t l)
{
    char *e = w[l - 1]; // pointer to last char
    while (w < e)
    {
        if (*w != *e) return false;
        ++w, --e; // move iterators inward
    }
    return true;
}

bool mirror(char *w, size_t l)
{
    return 0;
}

int main(int argc, char **argv)
{
    char *line;
    size_t len;
    while (getline(line, &len, stdin) != -1)
    {
        assert(line);
        len = strlen(line); // length
        line[--len] = '\0'; // exclude '\n' at end of line
        // determine what type of string it is
        if (palin(line, len))
        {
            if (mirror(line, len)) printf("%s\n\n", MIR_PALIN);
            else printf("%s\n\n", REG_PALIN);
        }
        else
        {
            if (mirror(line, len)) printf("%s\n\n", MIR_STR);
            else printf("%s\n\n", NOT_PALIN);
        }
        free(line);
    }
    return 0;
}
