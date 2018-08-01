
letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

n = int(input())
counts = dict()
for l in letters: counts[l] = 0
for z in range(n):
    text = input()
    for l in text.upper():
        if l in letters: counts[l] += 1
counts = list((counts[l],-ord(l)) for l in letters)
counts.sort(reverse=True) # descending counts, ascending letters
for item in counts:
    if item[0] == 0: break # exclude letters than dont appear
    print(chr(-item[1]),item[0])
