
cases = int(input())

for _ in range(cases):
    n,m,l = map(int,input().split())
    # n dominos
    G = dict() # domino x -> dominos y that x causes to fall
    for _ in range(m): # x causes y to fall
        x,y = map(int,input().split())
        if x not in G:
            G[x] = set()
        G[x].add(y)
    fallen = set()
    for _ in range(l): # dominos knocked by hand
        z = int(input())
        Q = set([z])
        while len(Q) > 0: # BFS
            nQ = set()
            for a in Q:
                if a in fallen: continue
                if a in G:
                    nQ |= G[a]
            fallen |= Q
            Q = nQ
    print(len(fallen))
