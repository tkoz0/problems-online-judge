
case = 0
while True:
    case += 1
    N, Q = map(int,input().split())
    if N == Q == 0: break
    marbles = list(int(input()) for z in range(N))
    marbles.sort()
    locs = dict() # map each number to its first location
    for i,m in enumerate(marbles):
        if not (m in locs): locs[m] = i+1
    print('CASE# %d:'%case)
    for z in range(Q):
        query = int(input())
        if query in locs: print('%d found at %d'%(query,locs[query]))
        else: print('%d not found'%query)
