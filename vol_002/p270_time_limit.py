import sys

def gcd(a,b):
    if a < 0: a = -a
    if b < 0: b = -b
    if a < b: a,b = b,a
    while b != 0: a,b = b,a%b
    return a

def slope(p,q):
    x1,y1 = p
    x2,y2 = q
    dx = x2 - x1
    dy = y2 - y1
    if dx == 0: return (0,1)
    g = gcd(dx,dy)
    dx //= g
    dy //= g
    if dx < 0: dx,dy = -dx,-dy
    return (dx,dy)

def answer(points):
    # linesets[i]: maps line slope --> partial result of points contained on
    # the line of that slope passing through point i
    linesets = [dict() for p in points]
    for i in range(1,len(points)):
        for j in range(i):
            # find slope between points i and j
            s = slope(points[i],points[j])
            if s in linesets[j]: # already have partial result
                linesets[j][s].add(points[i]) # include point i
                linesets[i][s] = linesets[j][s]
            else: # new slope for each, count both points
                linesets[j][s] = set([points[i],points[j]])
                linesets[i][s] = linesets[j][s]
    return max(max(len(s) for s in p.values()) for p in linesets)

cases = int(input())

for case in range(cases):
    if case == 0: input()
    points = []
    while True:
        try: line = input()
        except Exception: break
        if line == "": break
        x,y = map(int,line.split())
        points.append((x,y))
    assert len(points) > 0
    if case != 0: print()
    print(answer(points))
