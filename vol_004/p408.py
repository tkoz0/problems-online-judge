import sys

def gcd(a,b): # euclid gcd algorithm
    if a < b: a,b = b,a
    while b != 0: a, b = b, a%b
    return a

for line in sys.stdin:
    step, mod = map(int,line.split())
    # given allowed assumption fails
#    assert 1 <= step <= 100000
#    assert 1 <= mod <= 100000
    print('%10d%10d   ' % (step,mod), ('Good Choice\n' if gcd(step,mod) == 1
                                       else 'Bad Choice\n'))
