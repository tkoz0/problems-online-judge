
T = int(input())
assert T < 20

case = 0
for z in range(T):
    case += 1
    salaries = list(map(int,input().split()))
    salaries.sort()
    print('Case %d: %d' % (case,salaries[1]))
