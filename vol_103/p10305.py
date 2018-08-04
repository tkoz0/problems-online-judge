
while True:
    n, m = map(int,input().split())
    if n == m == 0: break
    assert 1 <= n <= 100
    outgoing = dict()
    incoming = dict()
    for z in range(1,n+1):
        outgoing[z] = set()
        incoming[z] = set()
    for z in range(m):
        i, j = map(int,input().split())
        outgoing[i].add(j)
        incoming[j].add(i)
    L = [] # kahn's algorithm
    S = list(z for z in incoming if len(incoming[z]) == 0)
    while len(S) != 0:
        n = S.pop()
        L.append(n)
        for m in set(outgoing[n]): # remove edge n-->m
            outgoing[n].remove(m)
            incoming[m].remove(n)
            if len(incoming[m]) == 0: S.append(m)
    # if a topological sorting exists, no edges should remain
    assert sum(len(z) for z in outgoing.values()) == 0
    assert sum(len(z) for z in incoming.values()) == 0
    print(' '.join(str(z) for z in L))
