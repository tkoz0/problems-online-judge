
n = int(input())

for z in range(n):
    s, d = map(int,input().split())
    if (s+d)%2 != 0: print('impossible'); continue
    small = s//2
    large = small + s%2
    small -= d//2
    large += d//2
    if small < 0: print('impossible'); continue
    print(large,small)
