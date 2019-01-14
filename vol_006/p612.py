
M = int(input())

for _ in range(M):
    input() # blank line
    n, m = map(int,input().split())
    assert 0 < n <= 50 # length
    assert 0 < m <= 100 # count
    strs = [input() for __ in range(m)]
    invs = []
    for s in strs:
        assert len(s) == n
        # just count inversions by brute force since theyre small strings
        invs__ = 0
        for i in range(n):
            for j in range(i+1,n):
                if s[i] > s[j]: invs__ += 1
        invs.append(invs__)
    to_sort = []
    for i in range(m):
        # sort by inversions, then input order
        to_sort.append((invs[i],i,strs[i]))
    to_sort = sorted(to_sort)
    for elem in to_sort:
        print(elem[2])
    if _ != M-1: print()
