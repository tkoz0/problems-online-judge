
T = int(input())

for case in range(1,1+T):
    assert input() == '' # each case starts with a blank line
    n, m = map(int,input().split()) # nodes, edges
    assert 2 <= n <= 100
    assert n-1 <= m <= n*(n-1)//2
    learn_units = list(map(int,input().split()))
    assert len(learn_units) == n # 1 for each graph node
    assert learn_units[0] == 0 # 0 at initial
    for i in range(1,n):
        assert 1 <= learn_units[i] <= 1000
    graph = [[] for _ in range(n)] # adjacency lists for each node
    for z in range(m): # read edges
        u, v = map(int,input().split()) # from u to v
        assert u != v and 0 <= u < n and 0 <= v < n
        graph[u].append(v) # add directed edge
    # now start at 0 and follow a greedy algorithm
    learned = learn_units[0]
    position = 0
    while len(graph[position]) > 0: # can move forward
        bestnextunits, bestnextnode = -1, -1
        for nextpos in graph[position]:
            if learn_units[nextpos] > bestnextunits:
                bestnextunits, bestnextnode = learn_units[nextpos], nextpos
        learned += bestnextunits
        position = bestnextnode
    print('Case %d: %d %d'%(case,learned,position))

