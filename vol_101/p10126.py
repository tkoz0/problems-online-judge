import sys

def word_gen(s): # generator to extract words from a string
    i = 0
    while True:
        j = i
        while j < len(s) and s[j].islower(): j += 1
        if i != j: yield s[i:j]
        if j == len(s): break
        i = j+1

first = True
while True:
    try: n = int(input())
    except EOFError: break
    counts = dict() # map words to frequency
    for line in sys.stdin:
        if line == 'EndOfText\n': break
        for word in word_gen(line.lower()):
            if not (word in counts): counts[word] = 0
            counts[word] += 1
    out = sorted(w for w in counts if counts[w] == n)
    if not first: print()
    else: first = False
    if len(out) == 0: print('There is no such word.')
    else: print('\n'.join(out))

