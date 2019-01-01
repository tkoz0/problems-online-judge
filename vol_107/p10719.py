import sys

for line in sys.stdin:
    k = int(line) # divide by (x-k)
    px = list(map(int,input().split())) # polynomial
    n = len(px)-1
    assert 1 <= n <= 10000
    qx = [px[0]] # synthetic division
    for i in range(1,n+1):
        qx.append(qx[-1]*k + px[i])
    r = qx.pop() # remainder is last number
    print('q(x):',' '.join(map(str,qx)))
    print('r =',r)
    print()
