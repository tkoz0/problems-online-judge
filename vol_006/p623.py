import sys
import math

for line in sys.stdin:
    n = int(line)
    assert n <= 1000
    print('%d!\n%d'%(n,math.factorial(n)))
