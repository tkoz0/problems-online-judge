
n = int(input())

for z in range(n):
    x, y = map(int,input().split())
    assert 0 <= x <= y < 2**31
    # minimize steps by using largest possible numbers
    # sequence 1+2+...+X+(X-1)+...+2+1 = (X+X-1)+(X-1+X-2)+...+(2-1)+(1-0) = X^2
    # pick largest X possible, fill in remaining by repeating steps (dif 0)
    # remaining space cant be larger than 2X (less than (X+1)^2-X^2)
    # if rem=0: none, if rem<=X, repeat 1, if rem<=2X then repeat 2
    # 1 or 2 numbers can be found that sum to remaining space if necessary
    dif = y-x
    if dif == 0: print(0) # no steps necessary
    else:
        X = int(dif**(1/2))
        if X*X == dif: print(2*X-1) # no extra steps
        elif dif-X*X <= X: print(2*X) # 1 extra step
        else: print(2*X+1) # 2 extra steps
