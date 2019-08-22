m,n = map(int,input().split()) # m is x direction, n is y direction
# game played in [1,m]x[1,n]
assert 2 < m < 51 and 2 < n < 51
wall_cost = int(input())
p = int(input())
assert p >= 0

# indexes are (x,y) or [x][y]
bumpers = [[False]*(n+1) for _ in range(m+1)] # which grid points are bumpers
value = dict() # map bumper position to value
cost = dict() # map bumper position to cost

for _ in range(p):
    x,y,v,c = map(int,input().split())
    assert 1 <= x <= m
    assert 1 <= y <= n
    # note that value and cost can be negative
    bumpers[x][y] = True
    value[(x,y)] = v
    cost[(x,y)] = c

def rot(dx,dy): # rotate movement vector (clockwise 90 degree)
    if (dx,dy) == (1,0): return (0,-1)
    if (dx,dy) == (0,1): return (1,0)
    if (dx,dy) == (-1,0): return (0,1)
    if (dx,dy) == (0,-1): return (-1,0)
    assert 0

def rev(dx,dy): # reverse movement vector
    return (-dx,-dy)

def wall(x,y): # is it a wall
    global m,n
    return x == 1 or x == m or y == 1 or y == n

def on_grid(x,y): # on the grid
    global m,n
    return (1 <= x <= m) and (1 <= y <= n)

total_points = 0

import sys
for line in sys.stdin:
    xi,yi,direction,life = map(int,line.split())
    assert not wall(xi,yi)
    print('ball %d,%d,%d,%d'%(xi,yi,direction,life))
    assert 1 <= xi <= m
    assert 1 <= yi <= n
    # determine movement vector
    if direction == 0: dx,dy = 1,0
    elif direction == 1: dx,dy = 0,1
    elif direction == 2: dx,dy = -1,0
    elif direction == 3: dx,dy = 0,-1
    else: assert 0
    assert life > 0

    points = 0
    x,y = xi,yi
    assert (not bumpers[x][y]) and (not wall(x,y))
    while life > 0: # ball loop
        if bumpers[x][y]:
            print('    hit %d,%d'%(x,y))
            points += value[(x,y)]
            life -= cost[(x,y)]
            dx,dy = rot(dx,dy)
        # attempt to move
        if not on_grid(x+dx,y+dy): # wall, rebound
            assert wall(x,y)
            dx,dy = rev(dx,dy)
            life -= wall_cost
        x,y = x+dx, y+dy
        life -= 1
        print('    move to %d,%d'%(x,y))
    print('    end %d,%d life=%d'%(x,y,life))
    if bumpers[x][y]: points += value[(x,y)] # add points (????)
    print(points)
    total_points += points

print(total_points)
