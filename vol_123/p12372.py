import sys

T = int(input())
assert T <= 100

for z in range(T):
    L, W, H = map(int,input().split())
    assert 1 <= L <= 50
    assert 1 <= W <= 50
    assert 1 <= H <= 50
    print('Case %d: %s' % (z+1,'good' if L<=20 and W<=20 and H<=20 else 'bad'))
