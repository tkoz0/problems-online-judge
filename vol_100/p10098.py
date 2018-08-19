
n = int(input())
for z in range(n): # start sorted, go in lexicographic order
    s = sorted(input())
    ls = len(s)
    while True:
        print(''.join(s))
        i1 = ls-1
        while i1 != 0 and s[i1-1] >= s[i1]: i1 -= 1 # break decreasing
        i1 -= 1
        if i1 == -1: break # all decreasing
        i2 = ls-1
        while s[i2] <= s[i1]: i2 -= 1 # find smallest greater value
        s[i1], s[i2] = s[i2], s[i1]
        i1 += 1
        i2 = ls-1
        while i1 < i2: # sort end portion increasing
            s[i1], s[i2] = s[i2], s[i1]
            i1 += 1
            i2 -= 1
    print()
