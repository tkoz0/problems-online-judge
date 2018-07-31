
T = int(input())
assert T <= 50

case = 0
for z in range(T):
    case += 1
    print('Case %d: %d'%(case,max(list(map(int,input().split()))[1:])))
