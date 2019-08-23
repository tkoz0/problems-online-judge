
g = dict() # dag
q = set() # topsort queue
indeg = dict() # node --> indegree
topsort = []

def topsort_search():
    global g,q,indeg,topsort
    if len(q) == 0: # check if valid topsort
#        print('graph =',g,'topsort =',topsort)
        assert sum(len(g[adj]) for adj in g) == 0 # no edges
        assert len(topsort) == len(g)
        print(''.join(topsort))
        return
    for n in sorted(q): # recurse on each removal possibility
        q.remove(n)
        topsort.append(n)
        removed_edges = []
        added_to_q = []
        for m in set(g[n]): # outgoing edges
            g[n].remove(m)
            indeg[m] -= 1
            removed_edges.append((n,m))
            if indeg[m] == 0:
                q.add(m)
                added_to_q.append(m)
        topsort_search()
        #backtrack
        for e in removed_edges:
            g[e[0]].add(e[1])
            indeg[e[1]] += 1
        for e in added_to_q: q.remove(e)
        topsort.pop()
        q.add(n)

def print_topsorts(): # compute all topological sorts
    global g,q,indeg,topsort
    indeg = dict()
    for v in g: indeg[v] = 0
    for u in g: # compute indegrees
        for v in g[u]:
            indeg[v] += 1
    q = set(n for n in indeg if indeg[n] == 0)
    topsort = []
    topsort_search()

import sys
first = True
for line in sys.stdin:
    vars = set(line.split())
    assert 2 <= len(vars) <= 20
    g = dict()
    for v in vars: g[v] = set()
    constrstr = input().split()
    assert len(constrstr) % 2 == 0
    assert 1 <= len(constrstr)//2 <= 50
    for i in range(0,len(constrstr),2): # make dag
        g[constrstr[i]].add(constrstr[i+1]) # (index i) < (index i+1) relation
#    print('constructed g =',g)
    if first: first = False
    else: print()
    print_topsorts()
