import sys

letters = set('ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz')

for line in sys.stdin:
    # replace all non letters with spaces
    for asci in range(33,127):
        if not (chr(asci) in letters): line = line.replace(chr(asci),' ')
    print(len(line.split())) # only contains letters now
