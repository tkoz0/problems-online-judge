
def bandw(graph,order):
    pass # TODO compute bandwidth given an order

def optimal(graph):
    order = sorted(graph.keys()) # start in lexico min
    opt_order = order[:]
    opt_bandw = bandw(graph,opt_order)
    # TODO iteratively permute through all possible orders
    # TODO make functions to compute the bandwidth
    # TODO consider a mapping from node to index in the order
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
