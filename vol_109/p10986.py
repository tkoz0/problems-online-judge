
N = int(input())

for case in range(1,1+N):
    n, m, S, T = map(int,input().split())
    assert 2 <= n <= 20000 # number of servers [0,n-1]
    assert 0 <= m <= 50000 # number of connections
    assert 0 <= S < n # source server
    assert 0 <= T < n # destination server
    assert S != T
    graph = [[] for _ in range(n)]
    for _ in range(m): # read edges to build graph
        s1, s2, w = map(int,input().split())
        assert 0 <= s1 < n
        assert 0 <= s2 < n
        assert 0 <= w <= 10000
        if s1 != s2:
            graph[s1].append((s2,w))
            graph[s2].append((s1,w))

    # use dijkstra's algorithm to find shortest path from S to T
    inf = 10000*20000 # guaranteed to be larger than any possible path
    dist = [inf]*n # default to infinity
    dist[S] = 0 # source

    # quick priority queue setup O(n)
    pq = [(inf,_) for _ in range(n)] # (priority/distance,server num)
    pqi = list(range(n)) # map server num --> index in priority queue
    pq[S] = (0,S)
    pqi[0], pqi[S] = pqi[S], pqi[0]
    pq[0], pq[S] = pq[S], pq[0]

    # main loop, compute distances with dijstra's algorithm
    while len(pq):
        distu, u = pq[0] # pop min (dist, server num)
        pq[0] = pq[-1]
        pqi[u] = -1 # not in priority queue anymore
        pq.pop()
        if len(pq): # not empty after pop
            pqi[pq[0][1]] = 0

        # sift down to fix heap by swapping with min child (if smaller)
        i = 0
        while 2*i+1 < len(pq): # has left child
            si = i # swap index
            if pq[2*i+1][0] < pq[si][0]: si = 2*i+1 # swap left preferred
            if 2*i+2 < len(pq) and pq[2*i+2][0] < pq[si][0]:
                si = 2*i+2 # swap right preferred
            if si == i: break # correct position
            pqi[pq[i][1]], pqi[pq[si][1]] = pqi[pq[si][1]], pqi[pq[i][1]]
            pq[i], pq[si] = pq[si], pq[i]
            i = si # for next sift

        for v,w in graph[u]: # adjacent vertices v
            if pqi[v] == -1: continue # not in priority queue
            dist2 = distu + w
            if dist2 < dist[v]:
                dist[v] = dist2
                pq[pqi[v]] = (dist2,v) # adjust priority

                # take v and sift up since its distance decreased
                i = pqi[v]
                while i > 0 and pq[(i-1)//2][0] > pq[i][0]:
                    pqi[pq[i][1]], pqi[pq[(i-1)//2][1]] = \
                        pqi[pq[(i-1)//2][1]], pqi[pq[i][1]]
                    pq[i], pq[(i-1)//2] = pq[(i-1)//2], pq[i]
                    i = (i-1)//2

    # output distance to destination
    if dist[T] == inf: print('Case #%d: unreachable'%case)
    else: print('Case #%d: %d'%(case,dist[T]))
