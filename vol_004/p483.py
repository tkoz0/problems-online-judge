import sys

for line in sys.stdin: print(' '.join(list(w[::-1] for w in line.split())))
