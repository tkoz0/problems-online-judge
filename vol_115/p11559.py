import sys

for line in sys.stdin:
    N, B, H, W = map(int,line.split())
    assert 1 <= N <= 200 # participants
    assert 1 <= B <= 500000 # budget
    assert 1 <= H <= 18 # hotels
    assert 1 <= W <= 13 # number of weeks
    mincost = 200*10000+1 # maximum possible N*p in this problem + 1
    for hotel in range(H):
        p = int(input())
        assert 1 <= p <= 10000 # price per person
        beds = list(map(int,input().split())) # available on each weekend
        assert len(beds) == W
        # cost = N*p if N <= beds available
        if max(beds) >= N: mincost = min(mincost, N*p)
    if mincost > B: print('stay home')
    else: print(mincost)
