import sys

repr = { 'B': 1, 'F': 1, 'P': 1, 'V': 1,
         'C': 2, 'G': 2, 'J': 2, 'K': 2, 'Q': 2, 'S': 2, 'X': 2, 'Z': 2,
         'D': 3, 'T': 3,
         'L': 4,
         'M': 5, 'N': 5,
         'R': 6 }

for line in sys.stdin:
    digits = []
    for c in line:
        if c in repr: digits.append(repr[c])
        else: digits.append(0)
    output = []
    prev = 0
    for d in digits:
        if d != 0 and d != prev: output.append(d)
        prev = d
    print(''.join(str(d) for d in output))
