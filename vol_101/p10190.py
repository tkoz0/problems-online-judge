import sys

for line in sys.stdin:
    n, m = map(int,line.split())
    # cannot create division sequence (length at least 2)
    if m < 2 or n == 0 or m > n: print('Boring!'); continue
    seq = [n]
    while n > 1: # try to make a sequence that works
        if n % m != 0: break
        n //= m # will get smaller since m >= 2
        seq.append(n)
    # successfully reached 1
    if seq[-1] == 1: print(' '.join(map(str,seq)))
    else: print('Boring!')
