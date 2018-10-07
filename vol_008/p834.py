import sys

def gcd(a,b):
    if a < b: a, b = b, a
    while b != 0: a, b = b, a%b
    return a

for line in sys.stdin:
    n, d = map(int,line.split())
    n, d = n // gcd(n,d), d // gcd(n,d)
    seq = []
    while d != 1:
        i = n//d
        seq.append(i)
        n -= i*d
        n, d = d, n # swap for 1/(fraction)
        n, d = n // gcd(n,d), d // gcd(n,d)
    seq.append(n)
    print('[%d;%s]'%(seq[0],','.join(str(s) for s in seq[1:])))
