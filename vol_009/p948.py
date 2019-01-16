
N = int(input())
assert 1 <= N <= 500

fibs = [0,1]
while fibs[-1] < 100000000: # generate
    fibs.append(fibs[-1]+fibs[-2])

def fib_base(n):
    global fibs
    i = len(fibs)-1
    while fibs[i] > n: i -= 1 # find first in representation
    result = ''
    while i >= 2: # skip indexes 0,1 since we only need a single 1 for this
        if fibs[i] <= n:
            result += '1'
            n -= fibs[i]
            i -= 1
            if i >= 2: # must skip one
                result += '0'
                i -= 1
        else:
            result += '0'
            i -= 1
    assert n == 0
    return result


for _ in range(N):
    n = int(input())
    assert 1 <= n < 100000000
    print('%d = %s (fib)'%(n,fib_base(n)))
