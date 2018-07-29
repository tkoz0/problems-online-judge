import sys

for line in sys.stdin:
    v, t = map(int,line.split())
    print(2*v*t) # moves at v for 2t time
