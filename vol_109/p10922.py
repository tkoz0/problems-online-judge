
while True:
    s = input()
    dsum = sum(int(c) for c in s)
    degree = 1
    if dsum == 0: break
    while dsum > 9:
        dsum = sum(int(c) for c in str(dsum))
        degree += 1
    if dsum == 9:
        print(s,'is a multiple of 9 and has 9-degree %d.'%degree)
    else: print(s,'is not a multiple of 9.')
