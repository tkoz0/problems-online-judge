import math

def dist(x1,y1,x2,y2): return math.sqrt((x1-x2)**2 + (y1-y2)**2)

figs = [] # 3-tuple = circle(x,y,r), 4-tuple = rectangle(x1,x2,y1,y2)

while True:
    line = input().split()
    if line[0] == '*': break
    if line[0] == 'r': # rectangle
        r = tuple(map(float,line[1:]))
        figs.append((r[0],r[2],r[3],r[1]))
        assert r[0] < r[2] and r[3] < r[1]
    elif line[0] == 'c': # circle
        figs.append(tuple(map(float,line[1:])))
        assert figs[-1][2] > 0.0

ptnum = 0
while True:
    ptnum += 1
    try: x, y = map(float,input().split())
    except EOFError: break
    if x == 9999.9 and y == 9999.9: break
    inside = False
    for i,f in enumerate(figs):
        if len(f) == 3: # circle
            if dist(f[0],f[1],x,y) < f[2]:
                print('Point %d is contained in figure %d'%(ptnum,i+1))
                inside = True
        elif len(f) == 4: # rectangle
            if f[0] < x < f[1] and f[2] < y < f[3]:
                print('Point %d is contained in figure %d'%(ptnum,i+1))
                inside = True
    if not inside: print('Point %d is not contained in any figure'%ptnum)
