import sys

for line in sys.stdin:
    n, m = map(int,line.split())
    # cannot create division sequence
    if m < 2 or n == 0 or m > n: print('Boring!'); continue
    seq = [n]
    while n > 1:
        if n % m != 0: break
        n //= m
        seq.append(n)
    if seq[-1] == 1: print(' '.join(map(str,seq)))
    else: print('Boring!')
