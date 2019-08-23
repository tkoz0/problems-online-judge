import sys
import math

def grid(a,b):
    return math.floor(a)*math.floor(b)

def skew2(a,b):
    evenrowmax = math.floor(a) # rows 0,2,4,...
    rowleftover = a-math.floor(a) # extra space for offset rows
    # 1 less if not enough space to slant over by 0.5
    oddrowmax = evenrowmax - (0 if rowleftover >= 0.5 else 1)
    if b < 1.0: return 0
    else: # find number of rows (sqrt(3)/2) for each row except first
        rows = 1 + math.floor(2.0*(b-1.0)/math.sqrt(3.0))
        pairs = rows//2 # add up rows
        leftover = rows % 2
        return pairs*(evenrowmax+oddrowmax) + leftover*evenrowmax

def skew(a,b):
    return max(skew2(a,b),skew2(b,a))

for line in sys.stdin:
    a,b = map(float,line.split())
#    assert 0.0 < a < 2.0**7.0 and 0.0 < b < 2.0**7.0
    g,s = grid(a,b), skew(a,b)
    if s > g: print(s,'skew')
    else: print(g,'grid')

