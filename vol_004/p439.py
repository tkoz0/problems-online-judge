
letters = 'abcdefgh'

def gen_dijkstra(x,y): # generate distance grid with source at x,y
    dist = list(list(99 for _x in range(8)) for _y in range(8)) # infinity
    dist[x][y] = 0 # source
    vset = set()
    for _x in range(8):
        for _y in range(8): vset.add((_x,_y))
    while len(vset) != 0: # simple implementation without priority queue
        mindist = min(dist[z[0]][z[1]] for z in vset)
        v = None # choose vertex with minimum distance
        for z in vset:
            if dist[z[0]][z[1]] == mindist: v = z; break
        assert not (v is None)
        vset.remove(v)
        dist2 = 1+dist[v[0]][v[1]] # neighbors of v
        for delta in [(2,1),(2,-1),(1,2),(1,-2),(-1,2),(-1,-2),(-2,1),(-2,-1)]:
            n = (v[0]+delta[0],v[1]+delta[1]) # neighbor
            if not (0 <= n[0] < 8) or not (0 <= n[1] < 8): continue
            dist[n[0]][n[1]] = min(dist[n[0]][n[1]],dist2) # choose smaller
    return dist

data = list(list(None for _x in range(8)) for _y in range(8))
# replace with 2d arrays for distances given a starting point
# desired value would be data[startx][starty][endx][endy]
for x in range(8):
    for y in range(8):
        data[x][y] = gen_dijkstra(x,y)

while True:
    try: a, b = input().split()
    except EOFError: break
    ax = letters.find(a[0])
    ay = int(a[1])-1
    bx = letters.find(b[0])
    by = int(b[1])-1
    print('To get from %s to %s takes %d knight moves.'
          %(a,b,data[ax][ay][bx][by]))
