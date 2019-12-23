import sys

rems = [0]*3000
digits = [0]*3000

for line in sys.stdin:
    n, d = map(int,line.split())
    assert 1 <= min(n,d) and max(n,d) <= 3000
    int_part = n // d
    rem = n % d
    # cycle cannot be longer than d-1 (pidgeonhole principle)
    # if remainder 0 is encountered, expansion is not cyclic
    rems[0] = rem
    digits[0] = 0 # digit before decimal point
    cyclic = True
    for i in range(1,d):
        rem *= 10 # compute next digit and remainder
        digits[i], rem = divmod(rem,d)
        if rem == 0:
            cyclic = False
            digits_end = i+1 # 1 past end
            break
        rems[i] = rem
    if n % d == 0: digits_end = 1 # 1 past last index
    if cyclic:
        # find same remainder as rems[d-1]
        for i in range(d-2,-1,-1):
            if rems[i] == rems[d-1]:
                cycle_len = (d-1)-i
                break
        # find cycle start (will be index right before first to include)
        cycle_start = 0
        while rems[cycle_start] != rems[cycle_start+cycle_len]:
            cycle_start += 1
        before_cycle = ''.join(str(z) for z in digits[1:cycle_start+1])
        cycle_start += 1
        cycle_end = cycle_start + cycle_len
        if cycle_end > 1+50: cycle_part = ''.join(
            str(z) for z in digits[cycle_start:1+50])+'...'
        else: cycle_part = ''.join(
                str(z) for z in digits[cycle_start:cycle_end])
        print('%d/%d = %d.%s(%s)'%(n,d,int_part,before_cycle,cycle_part))
        print('   %d = number of digits in repeating cycle'%cycle_len)
    else:
        print('%d/%d = %d.%s(0)'%(n,d,int_part,
              ''.join(str(z) for z in digits[1:digits_end])))
        print('   1 = number of digits in repeating cycle')
    print()
