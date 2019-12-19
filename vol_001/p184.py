import sys
from functools import cmp_to_key

def int_input_gen():
    for line in sys.stdin:
        line = map(int,line.split())
        for i in line: yield i

def point_cmp(p,q): # point ordering
    if p[0] != q[0]: return p[0] - q[0] # x
    return p[1] - q[1] # y
point_key = cmp_to_key(point_cmp)

def point_set_cmp(p,q): # point set ordering (by points)
    i = 0
    while i < len(p) and i < len(q):
        if point_cmp(p[i],q[i]) != 0: return point_cmp(p[i],q[i])
        i += 1
    return len(p) - len(q)
point_set_key = cmp_to_key(point_set_cmp)

def coord_step(x,y): # divides by gcd(x,y) to get step amount
    a, b = max(abs(x),abs(y)), min(abs(x),abs(y))
    while b != 0: a, b = b, a % b
    return (x//a,y//a)

def in_bounds(x,y): return 0 <= x <= 9999 and 0 <= y <= 9999

def find_line_sets(points): # main computation function
    sets = []
    points_set = set(points) # for fast containment checking
    for i in range(len(points)): # for each possible pair
        for j in range(i+1,len(points)):
            line = [points[i],points[j]]
            step_x, step_y = coord_step(points[j][0]-points[i][0],
                                        points[j][1]-points[i][1])
            x, y = points[i] # starting point, move in step amounts
            xx, yy = x + step_x, y + step_y
            while in_bounds(xx,yy): # explore both directions
                if (xx,yy) in points_set: line.append((xx,yy))
                xx, yy = xx + step_x, yy + step_y
            xx, yy = x - step_x, y - step_y
            while in_bounds(xx,yy):
                if (xx,yy) in points_set: line.append((xx,yy))
                xx, yy = xx - step_x, yy - step_y
            line = list(set(line)) # remove duplicates
            if len(line) > 2: sets.append(sorted(line))
#    return list(frozenset(sets)) # remove duplicates
    return [list(ll) for ll in set(tuple(l) for l in sets)]

def print_point_set(s): # print list of points in desired format
    print(''.join('(%4d,%4d)'%p for p in s))

int_input = int_input_gen()

while True:
    points = []
    while True:
        points.append((next(int_input),next(int_input)))
        assert 0 <= points[-1][0] <= 9999 and 0 <= points[-1][1] <= 9999
        if points[-1] == (0,0): break # terminate input set
    points.pop()
    if len(points) == 0: break # input set is empty
    assert 3 <= len(points) <= 300
    line_sets = find_line_sets(points)
    line_sets.sort()
    if len(line_sets) == 0: print('No lines were found')
    else: print('The following lines were found:')
    for line_set in line_sets:
        print_point_set(line_set)
