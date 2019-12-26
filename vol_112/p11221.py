import math

T = int(input())
assert 1 <= T <= 60

def symm(grid,K): # tests symmetry across both diagonals
    for r in range(K):
        for c in range(K-1-r):
            if grid[r][c] != grid[K-1-c][K-1-r]: return False
    for r in range(K):
        for c in range(r):
            if grid[r][c] != grid[c][r]: return False
    return True

for case in range(1,1+T):
    L = input()
    #assert 0 < len(L) < 10000
    s = ''.join(c for c in L if c.isalpha())
    K = int(math.sqrt(len(s))) if int(math.sqrt(len(s)))**2 == len(s) else -1
    if K != -1: # test magic, set K=-1 if fail
        grid = [s[i:i+K] for i in range(0,len(s),K)]
        assert len(grid) == K and len(grid[-1]) == K
        if not symm(grid,K): K = -1
    print('Case #%d:'%case)
    if K == -1: print('No magic :(')
    else: print(K)
