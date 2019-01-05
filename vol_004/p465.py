import sys

for line in sys.stdin:
    print(line,end='')
    if line.find('+') != -1:
        a,b = map(int,line.split('+'))
        r = a+b
    elif line.find('*') != -1:
        a,b = map(int,line.split('*'))
        r = a*b
    else: assert 0
    assert a >= 0 and b >= 0
    if a > 2147483647: print('first number too big')
    if b > 2147483647: print('second number too big')
    if r > 2147483647: print('result too big')
