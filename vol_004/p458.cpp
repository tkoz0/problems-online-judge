#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char c;
    while (scanf("%c",&c) == 1)
    {
        if (c == '\n') printf("\n");
        else printf("%c",c-7);
    }
    return 0;
}
