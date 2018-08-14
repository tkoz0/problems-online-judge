import math

while True:
    N = int(input())
    if N == 0: break
    assert 1 <= N <= 2*10**9
    sq = int(math.sqrt(N-1)) # completed prior squares
    rem = N - sq*sq # number of steps to take
    if sq % 2 == 0: # going up left
        if rem <= sq+1: print(sq+1,rem)
        else: print(sq+1-(rem-sq-1),sq+1)
    else: # going right down
        if rem <= sq+1: print(rem,sq+1)
        else: print(sq+1,sq+1-(rem-sq-1))
