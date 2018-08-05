
n = int(input())

counts = dict()

for z in range(n):
    words = input().split()
    if not (words[0] in counts): counts[words[0]] = set()
    counts[words[0]].add(''.join(words[1:]))

for country in sorted(counts.keys()): print(country,len(counts[country]))
