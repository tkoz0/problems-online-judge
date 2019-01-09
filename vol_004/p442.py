import sys

n = int(input())
assert 1 <= n <= 26

matrices = dict() # letter -> (rows,cols)
for _ in range(n):
    matr, r, c = input().split()
    r, c = int(r), int(c)
    assert len(matr) == 1 and matr == matr.upper()
    assert r > 0 and c > 0
    assert not (matr in matrices)
    matrices[matr] = (r,c)

def parenthesis_check(s):
    open_parenthesis = 0
    for c in s:
        if c == '(': open_parenthesis += 1
        elif c == ')':
            open_parenthesis -= 1
            if open_parenthesis < 0: return False
    return open_parenthesis == 0

# matrix = (single capital letter)
# expression = matrix | (expression expression)
class expression: # tree data structure
    def __init__(self,a,b=None):
        self.a = a
        self.b = b
    # compute multiplications, return -1 if there is an error
    def multiplications(self):
        pass
    def _eval(self): # helper function
        pass

def make_expr(s,a,b): # current part to evaluate is [a,b)
    pass

for line in sys.stdin:
    expr = line[:-1]
    assert parenthesis_check(expr)
    tree = make_expr(expr,0,len(expr))
    mults = tree.multiplications()
    print('error' if mults < 0 else str(mults))
