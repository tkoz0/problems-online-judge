
while True:
    try: N = int(input())
    except EOFError: break
    assert 1 < N < 1000000000 and N % 2 == 1
    # line with N numbers means 1 + 3 + 5 + ... + N numbers total
    # this is sum 2n-1 from n=1 to n=(N+1)/2
    # there are (N+1)^2/4 numbers total so the highest is
    # 2*(N+1)^2/4-1 = (N+1)^2/2 - 1
    # sum the other 2 numbers to get: 3*(N+1)^2/2 - 1 - 3 - 5
    print(3*((N+1)**2)//2 - 9)
