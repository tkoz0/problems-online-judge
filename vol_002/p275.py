
rems = [0]*1000
digits = [0]*1000

def line50(s): return [s[i:i+50] for i in range(0,len(s),50)]

while True:
    n, d = map(int,input().split())
    if n == d == 0: break
    assert n > 0 and d > 0
    assert n < d < 1000
    rems[0] = n
    rem = n
    digits[0] = 0
    cyclic = True
    for i in range(1,d):
        rem *= 10
        digits[i], rem = divmod(rem,d)
        if rem == 0:
            cyclic = False
            last_digit = i
            break
        rems[i] = rem
    if not cyclic:
        print('\n'.join(line50('.'
              +''.join(str(z) for z in digits[1:1+last_digit]))))
        print('This expansion terminates.')
        print()
    else:
        for i in range(d-2,-1,-1):
            if rems[i] == rems[d-1]:
                cycle_len = d-1-i
                break
        cycle_start = 0
        while rems[cycle_start] != rems[cycle_start+cycle_len]: cycle_start += 1
        cycle_start += 1
        print('\n'.join(line50('.'
              +''.join(str(z) for z in digits[1:cycle_start+cycle_len]))))
        print('The last',cycle_len,'digits repeat forever.')
        print()
