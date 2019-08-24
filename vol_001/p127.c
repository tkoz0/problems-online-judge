#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

struct card { char value, suit; };

struct card deck[52];
int decknext;
struct card pile[52][52];
int pilelen[52];
int piles;

int move();

int main(int argc, char **argv)
{
    char trash;
    for (;;)
    {
        scanf("%c",&deck[0].value);
        if (deck[0].value == '#') break; // EOF
        scanf("%c",&deck[0].suit);
        scanf("%c",&trash);
        for (int i = 1; i < 52; ++i)
            scanf("%c%c%c",&deck[i].value,&deck[i].suit,&trash);
        decknext = 0;
        for (int i = 0; i < 52; ++i)
            pilelen[i] = 0;
        piles = 0;
        while (decknext < 52)
        {
//printf("drawing %c %c\n",deck[decknext].value,deck[decknext].suit);
            pile[piles][0] = deck[decknext++]; // draw next
            pilelen[piles++] = 1;
            while (move()); // do all moves possible
        }
        printf("%d pile",piles);
        if (piles != 1) printf("s");
        printf(" remaining:");
        for (int i = 0; i < piles; ++i)
            printf(" %d",pilelen[i]);
        printf("\n");
    }
    return 0;
}

int eq(struct card a, struct card b)
{
    return a.value == b.value || a.suit == b.suit;
}

int move()
{
    for (int i = 1; i < piles; ++i) // find left most card to move
    {
        // first try to move it 3 left
        if (i >= 3 && eq(pile[i-3][pilelen[i-3]-1],pile[i][pilelen[i]-1]))
        {
            pile[i-3][pilelen[i-3]++] = pile[i][pilelen[i]-1]; // move card
            --pilelen[i];
            if (pilelen[i] == 0) // consolidate piles to get rid of empty space
            {
                for (int j = i+1; j < piles; ++j) // move pile j 1 left
                {
                    pilelen[j-1] = pilelen[j];
                    for (int k = 0; k < pilelen[j]; ++k)
                        pile[j-1][k] = pile[j][k];
                }
                --piles;
            }
            return 1;
        }
        // try to move 1 left
        if (eq(pile[i-1][pilelen[i-1]-1],pile[i][pilelen[i]-1]))
        {
            pile[i-1][pilelen[i-1]++] = pile[i][pilelen[i]-1];
            --pilelen[i];
            if (pilelen[i] == 0)
            {
                for (int j = i+1; j < piles; ++j) // move pile j 1 left
                {
                    pilelen[j-1] = pilelen[j];
                    for (int k = 0; k < pilelen[j]; ++k)
                        pile[j-1][k] = pile[j][k];
                }
                --piles;
            }
            return 1;
        }
    }
    return 0;
}
