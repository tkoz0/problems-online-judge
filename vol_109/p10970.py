import sys

for line in sys.stdin:
    M, N = map(int,line.split())
    assert 1 <= M <= 300
    assert 1 <= N <= 300
    print(M*N-1) # always true regardless of cutting order
