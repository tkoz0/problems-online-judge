import math
# build a graph of hole centers and the 2 cheese mites positions

def cheese_diagonal(holepos):
    x,X,y,Y,z,Z = 0,0,0,0,0,0
    for x_,y_,z_ in holepos:
        x,y,z = min(x,x_),min(y,y_),min(z,z_)
        X,Y,Z = max(X,x_),max(Y,y_),max(Z,z_)
    return math.ceil(math.sqrt((x-X)**2 + (y-Y)**2 + (z-Z)**2))

case_num = 0
while True:
    case_num += 1
    n = int(input())
    if n == -1: break
    assert 0 <= n <= 100
    holepos = [] # list of (x,y,z)
    holerad = [] # list of radii
    for _ in range(n): # read hole data
        x,y,z,r = map(int,input().split())
        holepos.append((x,y,z))
        holerad.append(r)
    xa,ya,za = map(int,input().split()) # amelia position
    xo,yo,zo = map(int,input().split()) # other mite
    holepos.append((xa,ya,za)) # model mite positions as "holes" of radius 0
    holerad.append(0)
    holepos.append((xo,yo,zo))
    holerad.append(0)
    # amelia is node n, other mite is node n+1
    graph = [[0.0]*(n+2) for _ in range(n+2)]
    for i in range(n+2):
        for j in range(i+1,n+2):
            x1,y1,z1 = holepos[i]
            x2,y2,z2 = holepos[j]
            dist = math.sqrt((x1-x2)**2 + (y1-y2)**2 + (z1-z2)**2)
            if dist < holerad[i]+holerad[j]: # holes are linked
                graph[i][j] = graph[j][i] = 0.0
            else:
                cheese = dist-holerad[i]-holerad[j] # cheese on shortest path
                graph[i][j] = graph[j][i] = 10.0*cheese
    # find shortest path from node n to n+1 with n as the source
    inf = 1+10*cheese_diagonal(holepos) # multiply by 10 because time
    #print('inf =',inf)
    dists = [inf]*(n+2)
    dists[n] = 0.0
    done = [False]*(n+2)
    #print('dists =',dists)
    while True: # no priority queue because lazy
        i = -1
        for j in range(n+2): # find min dist node
            if done[j]: continue
            if i == -1: i = j
            elif dists[j] < dists[i]: i = j
        if i == -1: break # no unmarked node found
        #print('node =',i)
        #print('dists =',dists)
        assert dists[i] != inf
        done[i] = True # mark node
        for j in range(n+2): # adjacent vertices
            dist2j = dists[i]+graph[i][j]
            if dist2j < dists[j]:
                assert not done[j]
                dists[j] = dist2j
            #dists[j] = min(dists[j],dists[i]+graph[i][j])
    travel_time = dists[n+1]
    print('Cheese %d: Travel time = %d sec'%(case_num,round(travel_time)))
