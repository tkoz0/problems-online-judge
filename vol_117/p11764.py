
T = int(input())
assert T < 30

for z in range(T):
    N = int(input())
    assert 0 < N < 50
    walls = list(map(int,input().split()))
    assert len(walls) == N
    hi, lo = 0, 0
    for i in range(1,N):
        if walls[i] > walls[i-1]: hi += 1
        elif walls[i] < walls[i-1]: lo += 1
    print('Case %d: %d %d'%(z+1,hi,lo))
