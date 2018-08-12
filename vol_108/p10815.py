import sys

words = set()

for line in sys.stdin:
    w = ''
    for c in line.lower():
        if c in 'abcdefghijklmnopqrstuvwxyz': w += c # build current word
        else: # word breaks with non letter char
            if w != '': words.add(w)
            w = '' # reset for reading next word

for w in sorted(words): print(w)
