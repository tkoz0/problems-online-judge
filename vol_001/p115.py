# p,q --> p is child of q

parents = dict() # map vertex to parents
children = dict() # map vertex to children

import sys
for line in sys.stdin: # build tree
    p,q = line.split()
    assert len(p) < 31 and len(q) < 31 # problem statement limits
    if p == 'no.child': break
    # add to tree
    if not (p in parents):
        parents[p] = set()
        children[p] = set()
    if not (q in parents):
        parents[q] = set()
        children[q] = set()
    parents[p].add(q)
    children[q].add(p)

assert len(parents) <= 300 # max 300 names

from functools import reduce

def descendent(p,q): # p descendent of q number, -1 if not descendent
    descen = -1
    queue = set([p]) # for bfs
    while len(queue) > 0:
        queue = reduce(lambda x,y : x|y, (parents[z] for z in queue)) # union
        descen += 1
        if q in queue: return descen
    return -1

def ancestor(p,q): # p ancestor of q, -1 if not ancestor
    ances = -1
    queue = set([p]) # for bfs
    while len(queue) > 0:
        queue = reduce(lambda x,y : x|y, (children[z] for z in queue))
        ances += 1
        if q in queue: return ances
    return -1

def descenstr(i):
    if i == 0: return 'child'
    return ((i-1)*'great ')+'grand child'

def ancesstr(i):
    if i == 0: return 'parent'
    return ((i-1)*'great ')+'grand parent'

def cousin(p,q): # returns (n,m) "n cousin remove m", or None if no relation
    # bfs from p, find lowest parent that is also a parent of q
    descen = -1
    queue = set([p])
    common = None # common ancestor
    while len(queue) > 0:
        queue = reduce(lambda x,y : x|y, (parents[z] for z in queue))
        descen += 1
        for z in queue:
            if ancestor(z,q) != -1:
                common = z
                queue = set() # to terminate outer loop
                break
    if common is None: return None
    m = ancestor(common,p)
    n = ancestor(common,q)
    return (min(m,n),abs(m-n))

if 0: # debugger
    for a in parents.keys():
        for b in parents.keys():
            print('input %s %s'%(a,b))
            i = descendent(a,b)
            if i != -1:
                print(descenstr(i))
                continue
            i = ancestor(a,b)
            if i != -1:
                print(ancesstr(i))
                continue
            # check for cousins
            i = cousin(a,b)
            if i is None: print('no relation')
            elif i == (0,0): print('sibling')
            else:
                if i[1] == 0: print('%d cousin'%i[0])
                else: print('%d cousin removed %d'%i)
    quit()

for line in sys.stdin: # queries
#    print('input line == %s'%line,end='')
    a,b = line.split()
    if not (a in parents) or not (b in parents):
        print('no relation')
        continue
    i = descendent(a,b)
    if i != -1:
        print(descenstr(i))
        continue
    i = ancestor(a,b)
    if i != -1:
        print(ancesstr(i))
        continue
    # check for cousins
    i = cousin(a,b)
    if i is None: print('no relation')
    elif i == (0,0): print('sibling')
    else:
        if i[1] == 0: print('%d cousin'%i[0])
        else: print('%d cousin removed %d'%i)
