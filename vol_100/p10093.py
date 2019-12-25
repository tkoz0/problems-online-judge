import sys

alpha = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
to_val = dict() # digit character to numeric value
for i,c in enumerate(alpha): to_val[c] = i

for R in sys.stdin:
    R = R[:-1]
    if R[0] == '-': R = R[1:] # negate
    N = max(to_val[c] for c in R)
    N += 1 # smallest possible base
    if N < 2: N = 2
    while N <= 62: # try all possible bases
        val = to_val[R[0]]
        for i in range(1,len(R)): # convert to base N value
            val = val*N + to_val[R[i]]
        if val % (N-1) == 0: break # satisfies given condition
        N += 1
    if N == 63: print('such number is impossible!')
    else: print(N)
