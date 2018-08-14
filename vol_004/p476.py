import sys

rects = []
for line in sys.stdin: # read rectangles
    if line == '*\n': break
    line = line.split()
    assert line[0] == 'r'
    rect = tuple(map(float,line[1:])) # upper left, lower right
    assert rect[0] < rect[2] and rect[1] > rect[3]
    rects.append((rect[0],rect[2],rect[3],rect[1])) # x1,x2,y1,y2

pointnum = 0
for line in sys.stdin:
    pointnum += 1
    x, y = map(float,line.split())
    if x == 9999.9 and y == 9999.9: break
    contain = []
    for i,r in enumerate(rects):
        if r[0] < x < r[1] and r[2] < y < r[3]: # inside
            contain.append(i+1)
    if len(contain) == 0: print('Point %d is not contained in any figure'
                                %pointnum)
    else:
        for f in contain: print('Point %d is contained in figure %d'
                                %(pointnum,f))
