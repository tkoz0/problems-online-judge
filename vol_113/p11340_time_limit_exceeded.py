
N = int(input())
assert 0 < N <= 5

for z in range(N):
    K = int(input())
    assert 0 < K <= 100
    table = dict()
    for zz in range(K):
        line = input().split()
        table[line[0]] = int(line[1])
    M = int(input())
    assert 0 < M <= 150000
    paid = 0
    for zz in range(M):
        for c in input():
            try: paid += table[c]
            except KeyError: pass # no pay
    print('%d.%02d$'%divmod(paid,100))
