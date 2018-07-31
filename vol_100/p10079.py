
while True:
    N = int(input())
    if N < 0: break
    assert 0 <= N <= 210000000
    # 1 + (1 + 2 + ... + N)
    print(1+N*(N+1)//2)
