import sys

for line in sys.stdin:
    s, t = line.split()
    si = 0
    while si < len(s):
        pos = t.find(s[si])
        if pos == -1: break
        t = t[pos+1:]
        si += 1
    print('Yes' if si == len(s) else 'No')
