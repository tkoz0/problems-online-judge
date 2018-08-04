import sys

fibs = [0,1]
while len(fibs) <= 5000:
    fibs.append(fibs[-1]+fibs[-2])

for line in sys.stdin:
    n = int(line)
    print('The Fibonacci number for %d is %d' % (n,fibs[n]))
