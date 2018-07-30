
while True:
    a, b = map(int,input().split())
    if a == 0 and b == 0: break
    a = list(map(int,list(str(a)[::-1]))) # little endian
    b = list(map(int,list(str(b)[::-1])))
    if len(a) < len(b): a += [0]*(len(b)-len(a)) # same lengths
    elif len(b) < len(a): b += [0]*(len(a)-len(b))
    assert len(a) == len(b)
    c = [0]*(len(a)+1)
    carry, carries = 0, 0
    for col in range(len(a)):
        val = carry + a[col] + b[col]
        carry = val//10
        if carry != 0: carries += 1
        c[col] = val%10
    c[-1] = carry
    if carries == 0: print('No carry operation.')
    elif carries == 1: print('1 carry operation.')
    else: print('%d carry operations.' % carries)
