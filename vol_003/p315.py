import sys

def connected(adjlist):
    reachable = set()
    stack = [list(adjlist.keys())[0]] # pick 1 vertex to start at
    while len(stack) > 0:
        v = stack.pop()
        if not (v in reachable): # new vertex
            reachable.add(v)
            stack += list(adjlist[v]) # push adjacent to stack
    return len(reachable) == len(adjlist)

for line in sys.stdin:
    N = int(line)
    if N == 0: break # 0 terminates input
    assert N < 100
    if N == 1: print(0); continue # special case
    adjlist = dict()
    while True:
        place = list(map(int,input().split()))
        if len(place) == 1 and place[0] == 0: break # single 0 termination
        if not (place[0] in adjlist): adjlist[place[0]] = set()
        for adj in place[1:]: # add each edge bidirectionally
            adjlist[place[0]].add(adj)
            if not (adj in adjlist): adjlist[adj] = set()
            adjlist[adj].add(place[0])
    # place is critical if its removal (and its edges) disconnects the graph
    critical = 0
    for test in range(1,N+1): # try removing a vertex and its edges
        adjacent = adjlist.pop(test)
        for a in adjacent: adjlist[a].remove(test)
        if not connected(adjlist): critical += 1
        adjlist[test] = adjacent # restore graph
        for a in adjacent: adjlist[a].add(test)
    print(critical)
