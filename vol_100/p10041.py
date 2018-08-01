
def median(l): # returns floor(median)
    l.sort()
    if len(l) % 2 == 1: return l[len(l)//2]
    else: return (l[len(l)//2]+l[len(l)//2-1])//2

cases = int(input())

for z in range(cases):
    values = list(map(int,input().split()))
    r = values[0]
    s = values[1:]
    assert 0 < r < 500
    assert len(s) == r
    m = median(s)
    print(sum(abs(v-m) for v in s))
