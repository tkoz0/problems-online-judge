import sys

# use sieve of erasthenes to list primes up to limit
sieve = [True]*10001
for i in range(2,101):
    if not sieve[i]: continue # composite
    for j in range(i*i,10001,i): sieve[j] = False
primes = [3] # skip 2 and 5
for z in range(7,10001):
    if sieve[z]: primes.append(z)

def lnzdnf(n): # last nonzero digit of n factorial
    global primes
    twos = n // 2 # skip pairs of 2 and 5 since they multiply to 10
    z = 4
    while z <= n: twos += n//z; z *= 2
    fives = n // 5 # this essentially divides out the ending zeroes in n!
    z = 25
    while z <= n: fives += n//z; z *= 5
    residue = pow(2,twos-fives,10)
    for p in primes:
        if p > n: break
        primepow = n//p
        z = p*p
        while z <= n: primepow += n//z; z *= p
        residue = (residue*pow(p%10,primepow,10)) % 10
    return residue

for line in sys.stdin:
    N = int(line)
    assert 0 <= N <= 10000
    print('%5d -> %d' % (N,lnzdnf(N)))
