
T = int(input())

for z in range(T):
    N = int(input())
    assert 7 <= N <= 3650
    P = int(input())
    assert 1 <= P <= 100
    hartals = list(int(input()) for zz in range(P))
    days = [False]*(N+1) # index divisible by 7 = saturday
    for h in hartals:
        for d in range(0,N+1,h): days[d] = True
    print(sum(1 for d in range(N+1) if (days[d] and d%7 != 0 and d%7 != 6)))
