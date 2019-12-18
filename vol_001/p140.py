
def bandw(graph,order):
    indexof = dict() # node -> order index
    for i,node in enumerate(order): indexof[node] = i
    # compute maximum distance between 2 connected nodes
    return max(max(abs(indexof[u] - indexof[v])
                   for v in graph[u]) for u in graph)

def optimal(graph):
    order = sorted(graph.keys()) # start in lexico min
    opt_order = order[:]
    opt_bandw = bandw(graph,opt_order)
    # iteratively permute through all possible orders
    while True:
        i1 = len(order)-1 # digit that breaks left to right nonincreasing
        while i1 > 0 and order[i1-1] >= order[i1]:
            i1 -= 1 # if previous is at least current, move back
        i1 -= 1 # the next one back breaks the left to right nonincreasing
        if i1 == -1: break # whole order is in nonincreasing order
        i2 = len(order)-1 # larger digit to swap
        # at this point, we can find a larger digit moving i2 back (i2 > i1)
        while order[i2] <= order[i1]: i2 -= 1
        order[i1], order[i2] = order[i2], order[i1]
        # now, consider the section after i1
        # everything after i2 is <= i2 value
        # everything before i2 continues (right to left) in nondecreasing order
        i1 += 1 # sort [i1,i2] range by swapping since it is nonincreasing
        i2 = len(order)-1
        while i1 < i2:
            order[i1], order[i2] = order[i2], order[i1]
            i1 += 1
            i2 -= 1
        this_bandw = bandw(graph,order)
        if this_bandw < opt_bandw:
            opt_order, opt_bandw = order[:], this_bandw
    print(' '.join(opt_order),'->',opt_bandw)

import sys
for line in sys.stdin:
    if line[0] == '#': break # eof
    gstr = line[:-1].split(';')
    graph = dict() # undirected graph
    for record in gstr:
        node, adj = record.split(':')
        if not (node in graph): graph[node] = set()
        graph[node] |= set(adj)
        for u in set(adj):
            if not (u in graph): graph[u] = set()
            graph[u].add(node)
    assert len(graph.keys()) <= 8
    optimal(graph)
