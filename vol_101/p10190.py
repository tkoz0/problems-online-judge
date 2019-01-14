import sys

for line in sys.stdin:
    n, m = map(int,line.split())
    seq = []
    while n != 1:
        seq.append(n)
        if n % m != 0: break
        n //= m
    if n == 1: print(' '.join(map(str,seq+[1])))
    else: print('Boring!')

