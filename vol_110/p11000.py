
# by definitions: M(0)=0, M(n)=M(n-1)+F(n-1), F(0)=1, F(n)=M(n-1)+1
# substitute F(n-1) to get M(0)=0, M(1)=1, M(n)=M(n-1)+M(n-2)+1
# generate values, given that outputs wont exceed 2^32
M = [0,1]
while True:
    M.append(M[-1]+M[-2]+1)
    if M[-1] >= 2**32: break
F = [1]
while True:
    F.append(M[len(F)-1]+1)
    if F[-1] >= 2**32: break
Nlim = 0
while M[Nlim]+F[Nlim] < 2**32: Nlim += 1

while True:
    N = int(input())
    if N < 0: break
    assert N < Nlim
    print(M[N],M[N]+F[N])
    continue # OLD CODE BELOW
    # output: male bees, all bees
    m, f, fi = 0, 0, 1 # male, female, female immortal
    for y in range(N): # iterate all years
        m2 = f+m+fi
        f2 = m
        m = m2
        f = f2
    print(m,m+f+fi)
