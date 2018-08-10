
# generate data for all
data = list([0] for z in range(10))
for num in range(1,10000):
    for z in range(10): data[z].append(data[z][-1])
    z = num
    while z != 0:
        data[z%10][-1] += 1
        z //= 10

cases = int(input())
assert cases <= 20

for case in range(cases):
    N = int(input())
    assert N < 10000
    print(' '.join(str(data[d][N]) for d in range(10)))
