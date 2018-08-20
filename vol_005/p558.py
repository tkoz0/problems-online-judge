
c = int(input())

def neg_cycle(adj): # bellman-ford algorithm
    inf = 1000*len(adj) # no path can be longer so use this as infinity
    dist = [inf]*len(adj)
    dist[0] = 0 # use vertex 0 as the source
    for i in range(len(adj)-1): # repeat v-1 times (v vertices)
        for u in range(len(adj)):
            for v,w in adj[u]:
                if dist[u] != inf and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
    # if an improvement can be made, then a negative cycle exists
    for u in range(len(adj)):
        for v,w in adj[u]:
            if dist[u] + w < dist[v]: return True
    return False # no improvements found --> no negative cycles exist

for z in range(c):
    n, m = map(int,input().split())
    assert 1 <= n <= 1000 # star systems (0...n-1)
    assert 0 <= m <= 2000 # wormholes
    adj = list([] for y in range(n)) # adj[u] --> (v,w) (edge uv with weight w)
    for w in range(m):
        x, y, t = map(int,input().split())
        assert 0 <= x < n
        assert 0 <= y < n
        assert -1000 <= t <= 1000
        adj[x].append((y,t))
    if neg_cycle(adj): print('possible')
    else: print('not possible')
