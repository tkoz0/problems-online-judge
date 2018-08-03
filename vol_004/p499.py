import sys

for line in sys.stdin:
    freq = dict()
    for c in line[:-1]:
        if c.isupper() or c.islower():
            if c in freq: freq[c] += 1
            else: freq[c] = 1
    most = max(freq.values())
    out = ''
    for k in freq.keys():
        if freq[k] == most: out += k
    print(''.join(sorted(list(out))),most)
