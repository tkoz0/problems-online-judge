import sys

most = 7489
ways = [0]*(most+1)
ways[0] = 1
for c in [1,5,10,25,50]:
    for i in range(c,most+1):
        ways[i] += ways[i-c]

for line in sys.stdin:
    n = int(line)
    print(ways[n])
