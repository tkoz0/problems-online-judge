
def bicolor(adj):
    col = dict() # map vertices to their color (0=none,1=color1,2=color2)
    for v in adj.keys(): col[v] = 0
    stack = [0] # color vertices by alternating
    col[0] = 1 # pick color 1
    while len(stack) > 0:
        v = stack.pop()
        assert col[v] != 0
        adjcol = 1 if col[v] == 2 else 2
        for u in adj[v]:
            # unvisited, color with other color and add to stack
            if col[u] == 0: col[u] = adjcol; stack.append(u)
            elif col[u] != adjcol: return False # has same color
    # verify
    for v in adj.keys():
        for u in adj[v]:
            # allowed to assume graph is connected so any starting vertex choice
            # will lead to coloring every vertex
            assert col[v] != 0 and col[u] != 0
            if col[v] == col[u]: return False
    return True

while True:
    n = int(input())
    if n == 0: break
    assert 1 < n < 200
    l = int(input())
    adj = dict() # map vertices to set of vertices they connect to
    for z in range(l):
        a, b = map(int,input().split())
        if not (a in adj): adj[a] = set()
        if not (b in adj): adj[b] = set()
        adj[a].add(b)
        adj[b].add(a)
    print('BICOLORABLE.' if bicolor(adj) else 'NOT BICOLORABLE.')
