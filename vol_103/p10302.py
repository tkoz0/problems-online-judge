
while True:
    try: n = int(input())
    except EOFError: break
    print(n*n*(n+1)*(n+1)//4) # sum of cubes
