
T = int(input())
assert 1 <= T <= 100

case = 0
for z in range(T):
    case += 1
    a = int(input())
    b = int(input())
    assert 0 <= a <= b <= 100
    if a % 2 == 0: a += 1
    b += 1
    print('Case %d: %d' % (case,sum(range(a,b,2))))
