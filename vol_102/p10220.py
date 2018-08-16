
# generate digit sums
fds = [1]
fval = 1
for i in range(1,1+1000):
    fval *= i
    fval2 = fval
    s = 0
    while fval2 != 0:
        fval2, d = divmod(fval2,10)
        s += d
    fds.append(s)

while True:
    try: n = int(input())
    except EOFError: break
    assert 0 <= n <= 1000
    print(fds[n])
