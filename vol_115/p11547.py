
t = int(input())
assert 1 <= t <= 100

for z in range(t):
    n = int(input())
    assert -1000 <= n <= 1000
    n = 315*n+36962 # simplify expression
    if abs(n) < 10: print(0)
    else: print(str(n)[-2])
