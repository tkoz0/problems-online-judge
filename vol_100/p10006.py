
def carmichael(n): # non prime, passes fermat test for 2 <= a < n
    has_factor = False
    if n % 2 == 0: has_factor = True
    if not has_factor: # try odd divisors
        d = 3
        while d*d <= n:
            if n % d == 0:
                has_factor = True
                break
            d += 2
    if has_factor: # not prime, test a^n mod n == a for 2 <= a < n
        for a in range(2,n):
            if pow(a,n,n) != a: return False # failed fermat test
        return True # passed fermat test
    else: return False # prime

while True:
    n = int(input())
    if n == 0: break
    assert 2 < n < 65000
    if carmichael(n): print('The number %d is a Carmichael number.'%n)
    else: print('%d is normal.'%n)
