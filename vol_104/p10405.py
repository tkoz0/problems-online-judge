import sys

for line in sys.stdin:
    in1 = line[:-1]
    in2 = input()
    commonchars = set(list(in1)) & set(list(in2)) # set intersection
    s1, s2 = '', '' # form strings by excluding chars not in both
    for c in in1:
        if c in commonchars: s1 += c
    for c in in2:
        if c in commonchars: s2 += c
    arr = list(list(0 for y in range(len(s2)+1)) for z in range(len(s1)+1))
    for s1i in range(1,len(s1)+1):
        for s2i in range(1,len(s2)+1):
            if s1[s1i-1] == s2[s2i-1]: arr[s1i][s2i] = 1 + arr[s1i-1][s2i-1]
            else: arr[s1i][s2i] = max(arr[s1i-1][s2i], arr[s1i][s2i-1])
    print(arr[len(s1)][len(s2)])
