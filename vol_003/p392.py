import sys

def sign(n): return '-' if n < 0 else '+'

for line in sys.stdin:
    coeffs = list(map(int,line.split()))
    terms = []
    exp = 9
    for c in coeffs:
        exp -= 1
        if c == 0: continue
        if exp == 0:
            if len(terms) == 0: terms.append('%d'%c)
            else:
                terms.append(sign(c))
                terms.append(str(abs(c)))
        else:
            if len(terms) == 0:
                if abs(c) == 1:
                    if exp != 1: terms.append(('-' if c == -1 else '')
                                              +('x^%d'%exp))
                    else: terms.append(('-' if c == -1 else '')+('x'))
                else:
                    if exp != 1: terms.append('%dx^%d'%(c,exp))
                    else: terms.append('%dx'%c)
            else:
                if abs(c) == 1:
                    terms.append(sign(c))
                    if exp != 1: terms.append('x^%d'%exp)
                    else: terms.append('x')
                else:
                    terms.append(sign(c))
                    if exp != 1: terms.append('%dx^%d'%(abs(c),exp))
                    else: terms.append('%dx'%abs(c))
    if len(terms) == 0: print('0')
    else: print(' '.join(terms))
