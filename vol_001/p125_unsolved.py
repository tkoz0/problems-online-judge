import sys
def numgen():
    for line in sys.stdin:
        for n in map(int,line.split()):
            yield n
numbers = numgen()

def print_matr(M):
    for row in M: print(' '.join(str(i) for i in row))

M = None
g = None
n = None

from functools import reduce

# find cycle s can reach, then remove everything the cycle can reach
def remove_cycle_reachable(g2,s):
    visit = set()
    stack = [s]
    while len(stack) > 0:
        print('stack =',stack)
        u = stack.pop()
        if u in visit: # cycle found
            print('cycle with %d'%u)
            q = set([u])
            while len(q) > 0: # remove reachable vertices
                rem = list(q)[0]
                q |= g2[rem]
                g2.pop(rem) # remove vertex
                for adj in g2.values():
                    if rem in adj: adj.remove(rem)
            return True
        else:
            visit.add(u)
            for v in g2[u]: stack.append(v)
    return False # removed nothing

def set_infinities():
    global M,g,n
    for source in g:
        g2 = dict() # copy graph
        for z in g: g2[z] = set(g[z])
        # remove vertices for which infinite paths from source to it
        while remove_cycle_reachable(g2,source): pass
        for z in g:
            if not (z in g2): M[source][z] = -1 # infinite paths
        # TODO finite paths

city_num = 0
for edge_count in numbers:
    print('matrix for city %d'%city_num)
    city_num += 1
    g = dict()
    for _ in range(edge_count):
        j = next(numbers)
        k = next(numbers)
        if not (j in g): g[j] = set()
        if not (k in g): g[k] = set()
        assert j != k
        g[j].add(k)
    n = 1+max(g.keys())
    M = [[-2]*n for _ in range(n)]
    set_infinities() # infinite path pairs
