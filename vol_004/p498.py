
while True:
    try:
        c = list(map(int,input().split()))[::-1]
        x = list(map(int,input().split()))
    except EOFError: break
    print(' '.join(map(str, # evaluate polynomial for all x values
        ((sum(c[i]*(z**i) for i in range(len(c)))) for z in x))))
