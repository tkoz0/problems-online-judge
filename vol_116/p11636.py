import math

case = 0
while True:
    case += 1
    N = int(input())
    if N < 0: break
    assert 0 < N < 10001
    print('Case %d: %d' % (case,math.ceil(math.log2(N))))
