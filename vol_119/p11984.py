
T = int(input())
assert T <= 100

for case in range(T):
    C, d = map(int,input().split()) # initial celsius, d increase in farenheit
    Fi = (9.0/5.0)*C+32.0 # initial farenheit
    F = Fi + float(d)
    Cf = (5.0/9.0)*(F-32.0) # convert back to celsius
    print('Case %d: %.2f'%(case+1,Cf))
