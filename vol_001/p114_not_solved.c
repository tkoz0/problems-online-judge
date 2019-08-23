#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int m,n;
int on_grid(int x,int y)
{
    return 1 <= x && x <= m && 1 <= y && y <= n;
}

int main(int argc, char **argv)
{
    scanf("%d %d",&m,&n);
    assert(2 < m && m < 51);
    assert(2 < n && n < 51);
    int wall_cost;
    scanf("%d",&wall_cost);
    int p;
    scanf("%d",&p);
    assert(p>=0);

    int obstacle[51][51], value[51][51], cost[51][51];
    for (int i = 0; i < 51; ++i)
        for (int j = 0; j < 51; ++j)
            obstacle[i][j] = value[i][j] = cost[i][j] = 0;

    for (int x = 1; x <= m; ++x)
    {
        obstacle[x][1] = obstacle[x][n] = 1;
        cost[x][1] = cost[x][n] = wall_cost;
    }
    for (int y = 1; y <= n; ++y)
    {
        obstacle[1][y] = obstacle[m][y] = 1;
        cost[1][y] = cost[m][y] = wall_cost;
    }

    while (p--)
    {
        int x,y,v,c;
        scanf("%d %d %d %d",&x,&y,&v,&c);
        assert(on_grid(x,y));
        obstacle[x][y] = 1;
        value[x][y] = v;
        cost[x][y] = c;
    }

    int x,y,direc,life,total_points=0;
    while (scanf("%d %d %d %d",&x,&y,&direc,&life) == 4)
    {
        assert(!obstacle[x][y]);
        int dx,dy;
        if (direc == 0) dx=1,dy=0;
        else if (direc == 1) dx=0,dy=1;
        else if (direc == 2) dx=-1,dy=0;
        else if (direc == 3) dx=0,dy=-1;
        else assert(0);
        int points=0;
        while (life>1)
        {
            int xn=x+dx,yn=y+dy;
            if (obstacle[xn][yn])
            {
                if (dx==1) dx=0,dy=-1;
                else if (dy==1) dx=1,dy=0;
                else if (dx==-1) dx=0,dy=1;
                else if (dy==-1) dx=-1,dy=0;
                life -= cost[xn][yn];
                points += value[xn][yn];
            }
            else x=xn,y=yn;
            --life;
        }
        total_points+=points;
        printf("%d\n",points);
    }
    printf("%d\n",total_points);

    return 0;
}
