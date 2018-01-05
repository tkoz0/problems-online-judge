#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_STR_LEN 20
#define NOT_PALIN " -- is not a palindrome."
#define REG_PALIN " -- is a regular palindrome."
#define MIR_STR " -- is a mirrored string."
#define MIR_PALIN " -- is a mirrored palindrome."

bool palin(char *w, size_t l)
{
    char *e = &(w[l - 1]); // pointer to last char
    while (w < e)
    {
        if (*w != *e) return false;
        ++w, --e; // move iterators inward
    }
    return true;
}

bool mirror(char *w, size_t l)
{
    char *e = &(w[l - 1]);
    while (w < e)
    {
        switch (*e)
        {
        // chars whose mirrors are themselves
        case 'A':
        case 'H':
        case 'I':
        case 'M':
        case 'O':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case '1':
        case '8': if (*w != *e) return false; break;
        // chars who have no mirrors
        case 'B':
        case 'C':
        case 'D':
        case 'F':
        case 'G':
        case 'K':
        case 'N':
        case 'P':
        case 'Q':
        case 'R':
        case '4':
        case '6':
        case '7':
        case '9': return false;
        // chars whose mirrors are different from themselves
        case 'E': if (*w != '3') return false; break;
        case 'J': if (*w != 'L') return false; break;
        case 'L': if (*w != 'J') return false; break;
        case 'S': if (*w != '2') return false; break;
        case 'Z': if (*w != '5') return false; break;
        case '2': if (*w != 'S') return false; break;
        case '3': if (*w != 'E') return false; break;
        case '5': if (*w != 'Z') return false; break;
        default: assert(0); // chars should never be invalid
/*
        case 'A': if (*w != 'A') return false; break;
        case 'B':
        case 'C':
        case 'D': return false;
        case 'E': if (*w != '3') return false; break;
        case 'F':
        case 'G': return false;
        case 'H': // mirror of H and I is themselves
        case 'I': if (*w != *e) return false; break;
        case 'J': if (*w != 'L') return false; break;
        case 'K': return false;
        case 'L': if (*w != 'J') return false; break;
        case 'M': if (*w != 'M') return false; break;
        case 'N': return false;
        case 'O': if (*w != 'O') return false; break;
        case 'P':
        case 'Q':
        case 'R': return false;
        case 'S': if (*w != '2') return false; break;
        case 'T': // TUVWXY mirrors are themselves
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y': if (*w != *e) return false; break;
        case 'Z': if (*w != '5') return false; break;
        case '1': if (*w != '1') return false; break;
        case '2': if (*w != 'S') return false; break;
        case '3': if (*w != 'E') return false; break;
        case '4': return false;
        case '5': if (*w != 'Z') return false; break;
        case '6':
        case '7': return false;
        case '8': if (*w != '8') return false; break;
        case '9': return false;
        default: assert(0); // should never have invalid character
*/
        }
        ++w, --e;
    }
    return true;
}

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t arrlen;
    while (getline(&line, &arrlen, stdin) != -1)
    {
        assert(line);
        size_t len = strlen(line); // length
        line[--len] = '\0'; // exclude '\n' at end of line
        // determine what type of string it is
        if (palin(line, len))
        {
            if (mirror(line, len)) printf("%s%s\n\n", line, MIR_PALIN);
            else printf("%s%s\n\n", line, REG_PALIN);
        }
        else
        {
            if (mirror(line, len)) printf("%s%s\n\n", line, MIR_STR);
            else printf("%s%s\n\n", line, NOT_PALIN);
        }
    }
    if (line) free(line);
    return 0;
}
