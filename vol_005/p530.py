import sys

for line in sys.stdin:
    n, k = map(int,line.split())
    if n == 0: break
    assert 0 <= k <= n
    v = 1
    for z in range(min(k,n-k)): v *= n-z; v //= z+1
    print(v)
