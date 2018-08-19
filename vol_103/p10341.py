import math
import sys

# pe^(-x)+qsinx+rcosx+stanx+tx^2+u=0
# given p,r>=0 and q,s,t<=0
# take 1st derivative, function is strictly decreasing
p,q,r,s,t,u = 0.0,0.0,0.0,0.0,0.0,0.0
def eval(x):
    return p*math.exp(-x)+q*math.sin(x)+r*math.cos(x)+s*math.tan(x)+t*x*x+u
epsilon = 2**(-32) # acceptable difference allowed

for line in sys.stdin:
    p,q,r,s,t,u = map(float,line.split())
    assert 0.0 <= p <= 20.0
    assert 0.0 <= r <= 20.0
    assert -20.0 <= q <= 0.0
    assert -20.0 <= s <= 0.0
    assert -20.0 <= t <= 0.0
    if eval(0.0) < 0.0 or eval(1.0) > 0.0: print('No solution')
    else: # function intersects x axis on [0,1]
        x = 0.0 # try x values, adding 1/2, 1/4, ... binary searching solution
        a = 1.0/2.0
        while a != 0.0:
            if eval(x+a) >= 0.0: x += a
            a /= 2.0
        print('%.4f'%x)
