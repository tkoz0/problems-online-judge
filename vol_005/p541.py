
while True:
    n = int(input())
    if n == 0: break
    matr = list(list(map(int,input().split())) for z in range(n))
    rsum = list(sum(matr[r]) for r in range(n))
    csum = list(sum(matr[r][c] for r in range(n)) for c in range(n))
    rodd = list(r for r in range(n) if rsum[r] % 2 == 1)
    codd = list(c for c in range(n) if csum[c] % 2 == 1)
    if len(rodd) == len(codd) == 0: print('OK')
    elif len(rodd) == len(codd) == 1:
        # fix by changing bit at intersection
        # this will change the parity of its row and column
        print('Change bit (%d,%d)'%(rodd[0]+1,codd[0]+1))
    else: print('Corrupt')
