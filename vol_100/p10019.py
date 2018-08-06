
N = int(input())

for z in range(N):
    M = int(input())
    base2 = '{0:0b}'.format(M)
    b1 = base2.count('1')
    base16 = '{0:0b}'.format(int(str(M),16))
    b2 = base16.count('1')
    print(b1,b2)
