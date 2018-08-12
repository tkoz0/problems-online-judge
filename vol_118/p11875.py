
T = int(input())
assert T <= 100

for case in range(T):
    line = list(map(int,input().split()))
    N = line[0]
    assert 1 < N < 11 # number of players
    ages = line[1:] # given in strictly increasing order (or decreasing)
    assert len(ages) == N
    print('Case %d: %d'%(case+1,ages[N//2]))
