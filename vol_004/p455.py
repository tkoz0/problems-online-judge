
N = int(input())

for z in range(N):
    assert input() == ''
    s = input()
    rep = ''
    minper = len(s)
    for l in range(1,1+len(s)//2):
        if len(s) % l == 0 and s == s[:l]*(len(s)//l): minper = l; break
    if z != 0: print()
    print(minper)
