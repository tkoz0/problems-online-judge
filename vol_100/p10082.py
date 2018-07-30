import sys

r1 = '`1234567890-='
r2 = 'QWERTYUIOP[]\\'
r3 = 'ASDFGHJKL;\''
r4 = 'ZXCVBNM,./'

for line in sys.stdin:
    line = line[:-1]
    conv = ''
    for ch in line:
        assert ch != r1[0] and ch != r2[0] and ch != r3[0] and ch != r4[0]
        if ch in r1: conv += r1[r1.find(ch)-1]
        elif ch in r2: conv += r2[r2.find(ch)-1]
        elif ch in r3: conv += r3[r3.find(ch)-1]
        elif ch in r4: conv += r4[r4.find(ch)-1]
        else:
            assert ch == ' '
            conv += ch
    print(conv)
