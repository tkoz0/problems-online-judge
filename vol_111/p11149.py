from fractions import Fraction
import itertools

MOD = 10 # only need to print last digit

def identity(n): # identity matrix
    return [[(1 if r == c else 0) for c in range(n)] for r in range(n)]

def square(M): # returns M*M (with modulus)
    global MOD
    return [ [ (sum(M[r][z]*M[z][c] for z in range(len(M)))) % MOD
               for c in range(len(M))]
             for r in range(len(M))]

def multiply(A,B): # returns A*B (with modulus)
    global MOD
    assert len(A) == len(B)
    return [ [ (sum(A[r][z]*B[z][c] for z in range(len(A)))) % MOD
               for c in range(len(A))]
             for r in range(len(A))]

def subtract(A,B): # returns A-B (with modulus)
    global MOD
    assert len(A) == len(B)
    return [ [(A[r][c]-B[r][c])%MOD for c in range(len(A))]
             for r in range(len(A))]

# inverted result will contain fractions objects
def invert(M): # return inverted matrix, None if it doesnt exist
    N = len(M)
    X = [[Fraction(_c) for _c in _r] for _r in M] # copy, dont modify original
    Y = identity(len(M))
    # row reduce X to I and perform same operations on Y
    for pivC in range(N): # pivot column
        pivR = pivC # find pivot row
        while pivR < N and X[pivR][pivC] == 0: pivR += 1
        if pivR == N: return None # unable to find row for pivot
        if pivR != pivC: # perform row swap
            X[pivC], X[pivR] = X[pivR], X[pivC]
            Y[pivC], Y[pivR] = Y[pivR], Y[pivC]
        assert X[pivC][pivC] != 0
        m = X[pivC][pivC] # multiple
        for z in range(N): # make pivot cell 1
            X[pivC][z] /= m
            Y[pivC][z] /= m
        assert X[pivC][pivC] == 1
        # use pivot row to eliminate in column both up and down
        for r in itertools.chain(range(pivC),range(pivC+1,N)):
            # subtract X[r][pivC] * (row pivC) from row r
            m = X[r][pivC]
            for z in range(N):
                X[r][z] -= m * X[pivC][z]
                Y[r][z] -= m * Y[pivC][z]
            assert X[r][pivC] == 0 # should be eliminated
    return Y

def exponentiate(M,k): # return M^k (with given modulus)
    global MOD
    # identity matrix
    result = identity(len(M))
    base = [[_c for _c in _r] for _r in M] # copy matrix M
    while k > 0:
        if k % 2 == 1: result = multiply(result,base)
        k //= 2
        if k > 0: base = square(base) # needed for next iteration
    return result

def print_matrix(M):
    print('\n'.join(' '.join(str(_c) for _c in _r) for _r in M))

while True:
    n, k = map(int,input().split())
    if n == 0: break
    assert n <= 40
    assert k <= 1000000
    A = [list(map(int,input().split())) for _ in range(n)]
    for _ in A: assert len(_) == n

    # compute: A + A^2 + ... + A^k = S
    # result is S = (I - A)^-1 * (I - A^(k+1)) if (I-A) is invertible
    I = identity(len(A))
    prod1 = invert(subtract(I,A)) # may contain fractions
    if prod1 is None: # not invertible
        print('divisor not invertible')
    else:
        prod2 = subtract(I,exponentiate(A,k+1))
        # product should be fractions that represent integers
        # subtract I since it is not included
        print_matrix(subtract(multiply(prod1,prod2),I))
    print()

