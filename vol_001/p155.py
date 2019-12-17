
XMIN, XMAX = 0, 2048
YMIN, YMAX = 0, 2048

def fits(k,x,y): # does size k square at (x,y) fit on grid
    assert 1 <= k <= 512
    xm, xM = x - k, x + k
    ym, yM = y - k, y + k
    return XMIN <= xm < xM <= XMAX and YMIN <= ym < yM <= YMAX

def contains_point(k,x,y,X,Y): # does size k square center (X,Y) contain (x,y)
    xm, xM = X - k, X + k
    ym, yM = Y - k, Y + k
    return xm <= x <= xM and ym <= y <= yM

# x,y is point to count squares for, X,Y is center of square to draw
def count(k,x,y,X,Y): # count squares recursively
    if k < 1: return 0
    if fits(k,X,Y):
        xm, xM = X - k, X + k # for corners
        ym, yM = Y - k, Y + k
        # count this square, recursively count for placing squares at corners
        total = 0
        if contains_point(k,x,y,X,Y): total += 1
        total += count(k//2,x,y,xm,ym)
        total += count(k//2,x,y,xm,yM)
        total += count(k//2,x,y,xM,ym)
        total += count(k//2,x,y,xM,yM)
        return total
    return 0

import sys
for line in sys.stdin:
    k, x, y = map(int,line.split())
    if k == x == y == 0: break
    print('%3d'%count(k,x,y,(XMIN+XMAX)//2,(YMIN+YMAX)//2))
