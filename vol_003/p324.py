import math

r1 = ''.join('   (%d)%%5d' % x for x in range(0,5)) # format strings
r2 = ''.join('   (%d)%%5d' % x for x in range(5,10))

while True:
    num = int(input())
    if num == 0: break # end
    fstr = str(math.factorial(num))
    counts = list(fstr.count(ch) for ch in '0123456789')
    print('%d! --' % num)
    print(r1 % tuple(counts[:5]))
    print(r2 % tuple(counts[5:]))
