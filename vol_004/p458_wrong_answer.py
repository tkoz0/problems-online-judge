import sys

for line in sys.stdin:
#    print(''.join(chr(32+(ord(c)-32-7)%95) for c in line if c != '\n'))
    print(''.join(chr((ord(c)-7)%256) for c in line[:-1]))
