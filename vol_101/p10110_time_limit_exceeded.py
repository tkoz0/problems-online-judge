
while True:
    n = int(input())
    if n == 0: break
    perf_square = True
    count = 0
    while n % 2 == 0: n //= 2; count += 1
    if count % 2 == 1: perf_square = False
    if perf_square: # try odd divisors
        d = 3
        while d*d <= n:
            if n % d == 0:
                count = 1
                n //= d
                while n % d == 0: count += 1; n //= d
                if count % 2 == 1: perf_square = False; break
            d += 2
        if n != 1: perf_square = False
    print('yes' if perf_square else 'no')
