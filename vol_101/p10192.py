import sys

case = 0
for line in sys.stdin:
    case += 1
    s1 = line[:-1]
    if s1 == '#': break
    s2 = input()
    # longest common subsequence algorithm
    dat = [[0]*(1+len(s2)) for i in range(1+len(s1))]
    for i1 in range(len(s1)):
        for i2 in range(len(s2)):
            # equal, 1 + sequence excluding current char
            if s1[i1] == s2[i2]: dat[i1+1][i2+1] = 1+dat[i1][i2]
            # pick larger of previously computed
            else: dat[i1+1][i2+1] = max(dat[i1+1][i2],dat[i1][i2+1])
    print('Case #%d: you can visit at most %d cities.'
          %(case,dat[len(s1)][len(s2)]))

