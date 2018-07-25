
while True:
    n, r = map(int, input().split())
    if n == 0 and r == 0: break # end
    v = 1
    for z in range(min(r,n-r)):
        v *= n-z
        v //= z+1
    print('%d things taken %d at a time is %d exactly.' % (n,r,v))
