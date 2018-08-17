
case = 0
while True:
    case += 1
    N = int(input())
    if N <= 0: break
    print('Case %d: %d'%(case,sum((-1 if n == 0 else 1)
                                  for n in map(int,input().split()))))
