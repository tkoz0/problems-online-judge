
words = set()
while True:
    line = input()
    if line == '#': break
    for w in line.split(): words.add(w)

whash = dict()
for w in words:
    k = ''.join(sorted(w.lower()))
    if not (k in whash): whash[k] = set()
    whash[k].add(w)

out = []
for k in whash:
    if len(whash[k]) == 1: out += list(whash[k])

print('\n'.join(sorted(out)))
