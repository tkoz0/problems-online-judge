
T = int(input())

# a generator of a number must be smaller since
# N + digitsum(N) = M --> N < M
sg = dict() # map number to its smallest generator
for N in range(100000):
    M = N + sum(int(d) for d in str(N))
    if not (M in sg): # no generator found yet
        sg[M] = N

for z in range(T):
    N = int(input())
    assert 1 <= N <= 100000
    try: print(sg[N])
    except KeyError: print(0)
