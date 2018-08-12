
T = int(input())
assert 1 <= T <= 1000

for case in range(T):
    N = int(input())
    assert 1 <= N <= 1000
    items = []
    for z in range(N):
        P, W = map(int,input().split()) # price and weight
        assert 1 <= P <= 100
        assert 1 <= W <= 30
        items.append((P,W))
    G = int(input()) # number of people
    MW = list(int(input()) for z in range(G)) # max weights for each person
