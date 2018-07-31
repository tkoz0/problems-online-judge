
while True:
    K = int(input())
    if K == 0: break
    assert 0 < K <= 10**3
    N, M = map(int,input().split())
    assert -10**4 < N < 10**4 and -10**4 < M < 10**4
    for z in range(K):
        X, Y = map(int,input().split())
        if X == N or Y == M: print('divisa')
        elif X > N and Y > M: print('NE')
        elif X < N and Y > M: print('NO')
        elif X > N and Y < M: print('SE')
        elif X < N and Y < M: print('SO')
        else: assert 0
