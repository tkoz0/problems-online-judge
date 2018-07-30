
N = int(input())
#assert 0 < N <= 100
# problem stated this was range for N, caused runtime error on judge

for z in range(N):
    P = int(input())
    steps = 0
    while True:
        steps += 1
        P += int(str(P)[::-1])
        s = str(P)
        if s == s[::-1]: break
    print(steps,P)
