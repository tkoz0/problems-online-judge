m,n = map(int,input().split()) # m is x direction, n is y direction
# game played in [1,m]x[1,n]
assert 2 < m < 51 and 2 < n < 51
wall_cost = int(input())
p = int(input())
assert p >= 0

obstacle = [[False]*(n+1) for _ in range(m+1)] # walls or bumpers
value = [[0]*(n+1) for _ in range(m+1)] # points
cost = [[0]*(n+1) for _ in range(m+1)] # life lost

# setup numbers for walls
for _ in range(m+1):
    obstacle[_][1] = obstacle[_][n] = True
    cost[_][1] = cost[_][n] = wall_cost
for _ in range(n+1):
    obstacle[1][_] = obstacle[m][_] = True
    cost[1][_] = cost[m][_] = wall_cost

def on_grid(x,y):
    global m,n
    return (1 <= x <= m) and (1 <= y <= n)

for _ in range(p): # bumpers loop
    x,y,v,c = map(int,input().split())
    assert on_grid(x,y)
    obstacle[x][y] = True
    value[x][y] = v
    cost[x][y] = c

def rot(dx,dy): # rotate movement vector (clockwise 90 degree)
    if (dx,dy) == (1,0): return (0,-1)
    if (dx,dy) == (0,1): return (1,0)
    if (dx,dy) == (-1,0): return (0,1)
    if (dx,dy) == (0,-1): return (-1,0)
    assert 0

#print(obstacle)
#print(value)
#print(cost)

import sys # balls loop
total_points = 0
for line in sys.stdin:
    x,y,direc,life = map(int,line.split())
    assert not obstacle[x][y]
    dx,dy = [(1,0),(0,1),(-1,0),(0,-1)][direc] # movement vector
    points = 0
#    print('ball %s'%line,end='')
    steps = 0

    while life > 1: # 2nd loop attempt
        xn,yn = x+dx, y+dy
        if obstacle[xn][yn]:
            dx,dy = rot(dx,dy)
            life -= cost[xn][yn]
            points += value[xn][yn]
        else: x,y = xn,yn
        life -= 1

    while life > 0:
        steps += 1
#        if steps == 10: quit()
        if obstacle[x+dx][y+dy]:
            life -= 1
#            print('    hit %d,%d'%(x+dx,y+dy))
            if life > 0:
                points += value[x+dx][y+dy]
#                print('    plus %d'%(value[x+dx][y+dy]))
            life -= cost[x+dx][y+dy]
            dx,dy = rot(dx,dy)
        else:
            x,y = x+dx, y+dy
            life -= 1
#            print('    move %d,%d'%(x,y))
    print(points)
    total_points += points
print(total_points)
