import sys

def bfs_last(tree,root):
    q = [root] # current level
    v = set() # visited
    while True:
        q2 = []
        for node in q: # visit each on current level, put next level in queue
            v.add(node)
            for node2 in tree[node]:
                if not (node2 in v): q2.append(node2)
        if len(q2) == 0: break # done
        q = q2
    return q # last level of BFS search, farthest from root

# problem doesnt say anything about line structure of input so read ints 1
# at a time from standard input using this generator
def get_ints(stream):
    for line in stream:
        for i in map(int,line.split()):
            yield i

ints = get_ints(sys.stdin)
# use next(ints), StopIteration error when no more left

while True:
    try: N = next(ints)
    except StopIteration: break
    assert 3 <= N <= 5000

# note that: a tree contains non-leaf nodes iff it has at least 3 nodes
# also, if u-v is a longest path in the tree, the best root must be the 1 or 2
# middle nodes on this path, otherwise it cannot be a best root
# thus, all trees have either 1 or 2 best roots

    tree = dict() # build tree
    for z in range(1,1+N):
        vdegree = next(ints)
        tree[z] = set()
        for _ in range(vdegree):
            tree[z].add(next(ints))

    for u,adj in tree.items(): # make edges bidirectional
        for v in adj: tree[v].add(u)

# best root can be found by having a queue of leaf nodes and merging them
# together until there is 1 or 2 left (no proof given here)

    degs = dict()
    for k,v in tree.items(): degs[k] = len(v) # get degrees for queue
    queue = list(k for k in degs if degs[k] == 1) # get all leaves
    remain = len(degs) # vertices left in tree
    while remain > 2:
        queue2 = []
        for node in queue:
            degs[node] -= 1 # now zero, removed from tree
            remain -= 1
            for adj in tree[node]:
                degs[adj] -= 1 # decrease
                if degs[adj] == 1: queue2.append(adj) # became a leaf node
        queue = queue2
    # queue now has best roots
    print('Best Roots  :',' '.join(map(str,sorted(queue))))
    # to find worst roots, combine the farthest nodes from (either) best root
    worst = []
    for root in queue: worst += bfs_last(tree,root)
    print('Worst Roots :',' '.join(map(str,sorted(worst))))
