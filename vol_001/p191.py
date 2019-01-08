
n = int(input())

def intersect(a,b,c,d): # return intersection of [a,b] and [c,d]
    if a > b: a,b = b,a # reorder
    if c > d: c,d = d,c
    assert a <= b and c <= d
    beg = max(a,c)
    end = min(b,d)
    if beg > end: return None
    else: return [beg,end]

# c is between a and b (inclusive), checks for ordering of a and b
def between(a,b,c):
    if a < b: return a <= c <= b
    return b <= c <= a

# (px,py) on line (xs,ys) to (xe,ye)
# technically box determined by line points, assume (px,py) on the infinte line
def on_line(xs,ys,xe,ye,px,py):
    return between(xs,xe,px) and between(ys,ye,py)

for _ in range(n):
    xstart, ystart, xend, yend, xleft, ytop, xright, ybottom = \
            map(float,input().split())
#    assert xleft <= xright
#    assert ybottom <= ytop
    # line from (xstart,ystart) to (xend,yend)
    # box is [xleft,xright] cross [ybottom,ytop]

    # case 1: line is contained in rectangle
    if min(xleft,xright) <= min(xstart,xend) \
        and max(xstart,xend) <= max(xleft,xright) \
        and min(ybottom,ytop) <= min(ystart,yend) \
        and max(ystart,yend) <= max(ybottom,ytop):
        print('T')
        continue

    # not inside, so if line intersect rentangle, there is an intersection
    # must check for intersection with 4 rectangle segments
    vx, vy = xend-xstart, yend-ystart # vector that partially determines line
    ileft, itop, iright, ibottom = False, False, False, False # intersections
    xoverlap = intersect(xstart,xend,xleft,xright)
    yoverlap = intersect(ystart,yend,ybottom,ytop)
    if xoverlap: # not None
        # find intersection of line with y=ybottom and y=ytop
        # extend line with vector multiple to find intersection with y=...
        # check that the point is on the line
        if vy != 0.0: # vector should move along y
            # multiple from line start to intersect y=...
            c1 = (ybottom-ystart)/vy
            c2 = (ytop-ystart)/vy
            if between(xoverlap[0],xoverlap[1],xstart+c1*vx) \
                and on_line(xstart,ystart,xend,yend,xstart+c1*vx,ystart+c1*vy):
                ibottom = True
            if between(xoverlap[0],xoverlap[1],xstart+c2*vx) \
                and on_line(xstart,ystart,xend,yend,xstart+c2*vx,ystart+c2*vy):
                itop = True
            # if on_line(xstart,ystart,xend,yend,xstart+c1*vx,ystart+c1*vy):
            #     ibottom = True
            # if on_line(xstart,ystart,xend,yend,xstart+c2*vx,ystart+c2*vy):
            #     itop = True
    if yoverlap: # not None
        if vx != 0.0:
            c1 = (xright-xstart)/vx
            c2 = (xleft-xstart)/vx
            if between(yoverlap[0],yoverlap[1],ystart+c1*vy) \
                and on_line(xstart,ystart,xend,yend,xstart+c1*vx,ystart+c1*vy):
                iright = True
            if between(yoverlap[0],yoverlap[1],ystart+c2*vy) \
                and on_line(xstart,ystart,xend,yend,xstart+c2*vx,ystart+c2*vy):
                ileft = True
            # if on_line(xstart,ystart,xend,yend,xstart+c1*vx,ystart+c1*vy):
            #     iright = True
            # if on_line(xstart,ystart,xend,yend,xstart+c2*vx,ystart+c2*vy):
            #     ileft = True
        # find intersection of line with x=xleft and x=xright
    print('T' if (ileft or itop or iright or ibottom) else 'F')
#    print('bools',ileft,itop,iright,ibottom)

