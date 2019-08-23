
def dijkstra(g,a,b):
    inf = 1+sum(sum(g[v1][v2] for v2 in g[v1]) for v1 in g) # infinity
    dist = dict()
    for v in g: dist[v] = inf
    dist[a] = 0
    queue = [s for s in g]
    while len(queue) > 0:
        u = queue[0]
        queuei = 0
        for i in range(1,len(queue)): # pop min
            if dist[queue[i]] < dist[u]: u, queuei = queue[i], i
        if queue.pop(queuei) == b: # remove from queue
            return dist[b] # finished b
        for v in graph[u]: # explore neighbors
            dist[v] = min(dist[v],dist[u]+graph[u][v])
    return -1

while True:
    streets = []
    while True:
        try: streets.append(input())
        except EOFError: quit()
        if streets[-1] == 'deadend': break
    streets.pop() # remove deadend
#    print(streets)
    for s in streets: assert s[0] != s[-1]
    edgeset = set(s[0]+s[-1] for s in streets)
    assert len(edgeset) == len(streets)
    graph = dict() # node --> (neigbor --> length)
    for s in streets:
        if not (s[0] in graph): graph[s[0]] = dict()
        if not (s[-1] in graph): graph[s[-1]] = dict()
        graph[s[0]][s[-1]] = len(s)
        graph[s[-1]][s[0]] = len(s)
    odds = [s for s in graph if len(graph[s]) % 2 == 1]
    if len(odds) == 0: # all vertices even
        print(sum(len(s) for s in streets))
    else: # some basic graph theory to get solution
        assert len(odds) == 2
        # undirected graph with 2 odd vertices
        # make an euler cycle by adding edge connecting them
        # remove this edge, connect the broken cycle by shortest path between
        # the odd vertices
        print(sum(len(s) for s in streets) + dijkstra(graph,odds[0],odds[1]))
#        print(sum(len(s) for s in streets))

