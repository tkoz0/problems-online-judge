
T = int(input())
assert T <= 100

for case in range(1,1+T):
    D, M, Y, QY = map(int,input().split())
    # assume D valid
    assert 1 <= M <= 12
    assert 1850 <= Y <= 2016
    assert Y <= QY <= 3000
    if M != 2 or D != 29: print('Case %d: %d'%(case,QY-Y)) # simple case
    else:
        QY -= QY % 4 # last possible birthday
        Y += 4-(Y%4) # first possible birthday
        # count multiples of 100 that are not leap years
        count = 0
        for _y in range(Y+(100-(Y%100))%100,1+QY,100):
            if _y % 400 != 0: count += 1
        print('Case %d: %d'%(case,1+(QY-Y)//4-count))
