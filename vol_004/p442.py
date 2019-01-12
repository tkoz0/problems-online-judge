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
        # returns (rows,cols,multiplications)
        # if error (non matching dimensions), return None
        global matrices
        if self.b is None:
            if type(self.a) == str: # same matrix, just dimensions
                return (matrices[self.a][0],matrices[self.a][1],0)
            else: return self.a.multiplications()
        else: # has 2 expressions, compute results of each half first
            if type(self.a) == str:
                r1 = (matrices[self.a][0],matrices[self.a][1],0)
            else: r1 = self.a.multiplications()
            if type(self.b) == str:
                r2 = (matrices[self.b][0],matrices[self.b][1],0)
            else: r2 = self.b.multiplications()
            if (r1 is None) or (r2 is None): return None # error occurred
            # now multiply them together
            if r1[1] != r2[0]: return None # left cols mult = right rows
            # recursive multiplications + (result size) * (vector size)
            return (r1[0],r2[1],r1[2]+r2[2]+(r1[1]*r1[0]*r2[1]))

def make_expr(s,a,b): # current part to evaluate is [a,b)
#    print('make_expr: %s'%s[a:b])
    if s[a] == '(':
        i, open_p = a+1, 1
        while open_p != 0:
            if s[i] == '(': open_p += 1
            elif s[i] == ')': open_p -= 1
            i += 1
        ex1 = make_expr(s,a+1,i-1) # recursively build parse tree
    else:
        ex1 = s[a];
        i = a+1
        assert s[a] in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    if i == b: # only contained 1 component
        return expression(ex1)
    # parse 2nd part
    if s[i] == '(':
        j, open_p = i+1, 1
        while open_p != 0:
            if s[j] == '(': open_p += 1
            elif s[j] == ')': open_p -= 1
            j += 1
        assert j == b
        ex2 = make_expr(s,i+1,j-1)
    else:
        ex2 = s[i]
        assert i+1 == b
        assert s[i] in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    return expression(ex1,ex2)

for line in sys.stdin:
    expr = line[:-1]
    assert parenthesis_check(expr)
    tree = make_expr(expr,0,len(expr))
    mults = tree.multiplications()
    print('error' if (mults is None) else mults[2])
