import sys

# coin counting dynamic programming problem

coins = [1,5,10,25,50]
ways = [0]*30001
ways[0] = 1
for coin in coins:
    for i in range(coin,30001): ways[i] += ways[i-coin]

for line in sys.stdin:
    n = int(line)
    m = ways[n]
    if m == 1: print('There is only 1 way to produce %d cents change.'%n)
    else: print('There are %d ways to produce %d cents change.'%(m,n))
