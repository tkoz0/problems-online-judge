
N = int(input())
assert 0 < N < 20

def ordered_inc(l):
    for i in range(1,len(l)):
        if l[i-1] > l[i]: return False
    return True

def ordered_dec(l):
    for i in range(1,len(l)):
        if l[i-1] < l[i]: return False
    return True

print('Lumberjacks:')
for z in range(N):
    l = list(map(int,input().split()))
    if ordered_inc(l) or ordered_dec(l): print('Ordered')
    else: print('Unordered')
