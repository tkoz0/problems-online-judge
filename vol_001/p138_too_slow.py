import math

# not getting solution, ~3min (cpython / phenom ii x6 1055t)

printed = 0
N = 3
while printed != 10:
    # 1+2+...+N=N(N+1)/2 so find an X that splits the sum evenly
    # X = floor((-1+sqrt(1+2*(N^2+N)))/2)
    X = int((-1.0+math.sqrt(1+2*(N*N+N)))/2.0)
    left = X*(X-1)//2 # smaller numbers
    right = N*(N+1)//2 - X*(X+1)//2 # larger numbers
    assert left <= right
    while left <= right:
        left += X
        X += 1
        right -= X
        if left == right:
            printed += 1
            print('%10d%10d'%(X,N))
            break
    N += 1
