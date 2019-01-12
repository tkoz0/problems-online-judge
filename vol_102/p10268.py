
while True:
    try:
        x = int(input())
        c = list(map(int,input().split()))[::-1]
    except EOFError: break
    print(sum(i*c[i]*(x**(i-1)) for i in range(1,len(c))))
