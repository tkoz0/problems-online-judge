
case = 0
while True:
    case += 1
    n = int(input())
    if n == 0: break
    assert 1 < n <= 1000
    nums = []
    for _ in range(n):
        nums.append(int(input()))
    m = int(input())
    assert 0 < m < 25
    print('Case %d:'%case)
    for _ in range(m): # process queries
        pass
