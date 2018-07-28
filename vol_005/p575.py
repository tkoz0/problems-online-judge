
while True:
    n = input()
    if n == '0': break
    n = n[::-1] # start from least significant
    v = 0
    for i,d in enumerate(n):
        if d == '1': v += 2**(i+1)-1
        elif d == '2': v += 2**(i+2)-2
    print(v)
