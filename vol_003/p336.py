
def num_connected(adjlist,source):
    found = set()
    stack = [source]
    while len(stack) != 0:
        v = stack.pop()
        if not (v in found):
            found.add(v)
            stack += list(adjlist[v]) # push adjacent nodes
    return len(found)

# for simplicity, recurse everything rather than trying to optimize
def count_reachable(adjlist,source,ttl):
    reachable = set([source])
    componentsize = num_connected(adjlist,source)
    for z in range(ttl): # bfs search on ttl levels
        newlevel = set()
        for a in reachable:
            for b in adjlist[a]: newlevel.add(b)
        for a in newlevel: reachable.add(a)
        if len(reachable) == componentsize: break # reached every connected node
    return len(reachable)

case = 0
while True:
    line = input()
    if line == '': continue # skip empty line
    NC = int(line)
    if NC == 0: break
    pairs = []
    while True:
        raw = list(map(int,input().split()))
        pairs += list((raw[z],raw[z+1]) for z in range(0,len(raw),2))
        if pairs[-1] == (0,0): break # terminates input
    pairs.pop()
    queries = pairs[NC:]
    connections = pairs[:NC]
    adjlist = dict() # map vertices to which ones they connect to
    for connection in connections: # build adjacency lists
        if not (connection[0] in adjlist): adjlist[connection[0]] = set()
        if not (connection[1] in adjlist): adjlist[connection[1]] = set()
        adjlist[connection[0]].add(connection[1])
        adjlist[connection[1]].add(connection[0])
    assert len(adjlist) <= 30
    for query in queries:
        case += 1
        source = query[0]
        ttl = query[1]
        reachable = count_reachable(adjlist,source,ttl)
        print('Case %d: %d nodes not reachable from node %d with TTL = %d.'
              % (case,len(adjlist)-reachable,source,ttl))
