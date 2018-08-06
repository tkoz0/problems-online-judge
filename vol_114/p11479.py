
T = int(input())
assert T < 20

for case in range(1,T+1):
    side = sorted(map(int,input().split()))
    if side[2] < side[0] + side[1]: # valid
        if side[0] == side[1] == side[2]: print('Case %d: Equilateral' % case)
        elif side[0] == side[1] or side[1] == side[2]:
            print('Case %d: Isosceles' % case)
        else: print('Case %d: Scalene' % case)
    else: print('Case %d: Invalid' % case)
