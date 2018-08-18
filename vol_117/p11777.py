
T = int(input())
assert T < 100

for case in range(1,1+T):
    t1, t2, f, a, ct1, ct2, ct3 = map(int,input().split())
    score = float(t1+t2+f+a)
    score += (ct1+ct2+ct3-min(ct1,ct2,ct3))/2.0
    print('Case %d: '%case,end='')
    if score < 60.0: print('F')
    elif score < 70.0: print('D')
    elif score < 80.0: print('C')
    elif score < 90.0: print('B')
    else: print('A')
