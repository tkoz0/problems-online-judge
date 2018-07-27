
def factorize(n): # produce list of prime factors in increasing order
    assert n > 0
    f = []
    while n % 2 == 0: f.append(2); n //= 2 # factors 2
    d = 3
    while d*d <= n: # odd factors
        while n % d == 0: f.append(d); n //= d
        d += 2
    if n != 1: f.append(n) # last prime factor
    return f

while True:
    g = int(input())
    if g == 0: break
    assert -(2**31) < g < (2**31)
    f = map(str,factorize(abs(g))) # factors as strings
    if g > 0: print(g,'=',' x '.join(f))
    else: print(g,'= -1 x',' x '.join(f))
