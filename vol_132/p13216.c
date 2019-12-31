#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#define BASE 66
#define MOD 100
#define MAX_POW 1000

char n_buf[MAX_POW+1];
uint32_t powtable[MOD][11]; // powtable[n][p] = n**p % MOD

void init_powtable() // fast power computation by lookup
{
    uint32_t n,p,val;
    for (n = 0; n < MOD; ++n)
    {
        val = 1;
        powtable[n][0] = 1;
        for (p = 1; p < 11; ++p)
            powtable[n][p] = (val = (val*n) % MOD);
    }
}

int main(int argc, char **argv)
{
    uint32_t T,len,p,base,result;
    int r;
    char ch;
    init_powtable();
    r = scanf("%u",&T);
    assert(r == 1);
    assert(T && T <= 5000);
    r = scanf("%c",&ch);
    assert(r == 1 && ch == '\n');
    while (T--) // process each case
    {
        // read chars until \n
        len = 0;
        for (;; ++len)
        {
            r = scanf("%c",&n_buf[len]);
            assert(r == 1);
            if (n_buf[len] == '\n') break;
        }
        base = BASE % MOD;
        result = 1;
        while (len--) // main loop
        {
            result = (result*powtable[base][n_buf[len]-'0']) % MOD;
            base = powtable[base][10];
        }
        printf("%u\n",result);
    }
}
