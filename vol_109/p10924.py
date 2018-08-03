import sys

def value(c):
    if c.islower(): return 1+ord(c)-ord('a')
    else: return 27+ord(c)-ord('A')

def prime(n):
    if n == 1: return True # exception required for this problem
    if n < 2: return False
    if n < 4: return True
    if n % 2 == 0: return False
    d = 3
    while d*d <= n:
        if n % d == 0: return False
        d += 2
    return True

for line in sys.stdin:
    wsum = sum(value(c) for c in line[:-1])
    print('It is%s a prime word.' % ('' if prime(wsum) else ' not'))
