
sieve = [True]*1000000 # determines if a number is prime
for i in range(2,1000+1):
    if not sieve[i]: continue
    for j in range(i*i,1000000,i): sieve[j] = False

while True:
    try: N = int(input())
    except EOFError: break
    assert 1 < N < 1000000
    if sieve[N]:
        rev = int(str(N)[::-1])
        if rev != N and sieve[rev]: print('%d is emirp.'%N);
        else: print('%d is prime.'%N)
    else: print('%d is not prime.'%N)
