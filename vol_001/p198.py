import sys

data = dict() # map variable --> expression

## original and recursive evaluation variable, v='' for base call
#def try_print(orig,v=''): # return None if undefined,
#    global data
#    if v == '': v = orig # base recursion, evaluate original
#    elif v == orig: return None # cycle
#    # attempt to evaluate v
#    if not (v in data): return None
#    vals = dict() # map variables to evaluated values
#    i = 0
#    while i < len(data[v]):
#        if data[v][i].isalpha(): # parse variable
#            v2 = data[v][i]
#            i += 1
#            while i < len(data[v]) and data[v][i].isalnum():
#                v2 += data[v][i]
#                i += 1
#            result = eval_expr(v2,vals)
#        else: i += 1

vars_used = set() # for cycle detection
def compute(expr): # returns an integer or None if evaluation is unsuccessful
    global data, vars_used
    expr = expr.strip()
#    print('compute called with',expr)
    if expr == '': return None
#    if expr[0] == '(' and expr[-1] == ')': return compute(expr[1:-1]) # fails for expressions like (a+b)+(c+d)
    terms = []
    i = 0
    while i < len(expr): # parse terms
        if expr[i] == '(': # find matching close )
            depth = 1
            j = i+1
            while j < len(expr):
                if expr[j] == '(': depth += 1
                elif expr[j] == ')': depth -= 1
                if depth < 0: return None # invalid format
                if depth == 0: break # closed
                j += 1
            if depth != 0: return None # couldnt close
            terms.append(expr[i:j+1])
            i = j+1
        elif expr[i].isalpha(): # variable
#            print('found var starting with',expr[i])
            j = i+1
            while j < len(expr) and expr[j].isalnum(): j += 1
            terms.append(expr[i:j])
            i = j
        elif expr[i].isdigit() or expr[i] == '-': # number
            j = i+1
            while j < len(expr) and expr[j].isdigit(): j += 1
            terms.append(int(expr[i:j]))
            i = j
        elif expr[i] in ' \t\n': # skip whitespace
            i += 1
            continue
        else: return None # invalid format
        # should expect operator after this (unless its the last one)
        # search for EOS (end of string) or +,-,* operators
        while i < len(expr) and expr[i] in ' \t\n': i += 1;
        if i == len(expr): break # end of string
        if expr[i] in '+-*':
            terms.append(expr[i])
#            print('added operator',expr[i])
            i += 1
        else: return None # invalid format
    assert len(terms) % 2 == 1
#    print(terms) # 3 types of terms: parenthesis, variable, number
    for i in range(0,len(terms),2): # reformat terms
        if (type(terms[i]) is str) and terms[i][0] == '(':
            assert terms[i][-1] == ')'
            terms[i] = compute(terms[i][1:-1])
            if terms[i] is None: return None
        elif type(terms[i]) is str: # variable
#            print('found var',terms[i])
#            print(data,vars_used)
            if terms[i] in vars_used: return None # cycle detected
            assert terms[i][0].isalpha()
            if len(terms[i]) > 1: assert terms[i][1:].isalnum()
            if terms[i] in data: # get expression to use
#                print('computing with',data[terms[i]])
                tempvar = terms[i]
                vars_used.add(tempvar) # cannot reuse in recursion
                terms[i] = compute(data[terms[i]])
                vars_used.remove(tempvar)
            else: terms[i] = None
            if terms[i] is None: return None
        # else, number
    for i in range(0,len(terms),2): assert type(terms[i]) is int
    for i in range(1,len(terms),2): assert terms[i] in '+-*'
    # evaluate expression, first use *
    while '*' in terms:
        i = 1
        while terms[i] != '*': i += 2
        prod = terms[i-1]*terms[i+1]
        terms = terms[:i-1]+[prod]+terms[i+2:]
    result = terms[0]
    for i in range(1,len(terms),2):
        if terms[i] == '+': result += terms[i+1]
        elif terms[i] == '-': result -= terms[i+1]
        else: assert 0
    return result

#for line in sys.stdin: vars_used = set(); print(compute(line))
#quit()

for line in sys.stdin:
    line = line.strip()
    i = line.find(':=')
    if i == -1: # should be print or reset
        line = line.split()
        if len(line) >= 1 and line[0] == 'RESET':
            data = dict() # clear data
        elif len(line) >= 2 and line[0] == 'PRINT':
            vars_used = set()
            result = compute(line[1])
            if result is None: print('UNDEF') # print variable
            else: print(result)
    else:
        var = line[:i].strip()
        if var == '': continue # invalid
        if var[0].isalpha() and (len(var) == 1 or var[1:].isalnum()):
            data[var] = line[i+2:].strip()
        else: continue # invalid
