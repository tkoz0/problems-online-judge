import sys
from math import sqrt

for line in sys.stdin:
    i = int(line)
    # first find how many diagonals come before i, equivalently how many
    # diagonals there are up to i-1
    # the associated triangle number is n=(sqrt(8(i-1)+1)-1)/2
    # thus pick n=floor((sqrt(8(i-1)+1)-1)/2) as the number of diagonals that
    # come before i
    n = int((sqrt(8*(i-1)+1)-1)/2)
    s = i - n*(n+1)//2 # steps to take on next diagonal
    assert s > 0
    top = n+2 - s # (n+1)th diagonal
    bottom = s # sum on diagonal is n+2
    print('%d/%d'%(top,bottom))

