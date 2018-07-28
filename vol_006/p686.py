import math

limit = 2**15

sieve = [True]*limit # sieve of eratosthenes
for i in range(2,1+math.floor(math.sqrt(limit))):
    if not sieve[i]: continue
    for j in range(i*i,limit,i): sieve[j] = False

while True:
    n = int(input())
    if n == 0: break
    assert n % 2 == 0 and 4 <= n < limit
    count = 0
    for a in range(2,1+n//2):
        if sieve[a] and sieve[n-a]: count += 1
    print(count)
