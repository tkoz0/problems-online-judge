import sys

def preprocess_poly(poly):
    tmp = poly.split('+')
    tmp2 = []
    for t in tmp:
        t2 = t.split('-') # avoid losing - signs for coefficients
        for i in range(1,len(t2)):
            t2[i] = '-'+t2[i]
        tmp2 += t2
    # tmp2 contains coefficient strings
    if tmp2[0] == '': tmp2.pop(0) # empty result if expression starts with -
#    print('terms =',tmp2)
    polymap = dict() # map (x_exp,y_exp) --> coefficient
    for term in tmp2:
#        print('reading term',term)
        i = 0
        while i < len(term) and (term[i] in '-0123456789'): i += 1
        coeff = term[:i]
        if coeff == '': coeff = 1 # implicit 1
        elif coeff == '-': coeff = -1
        else: coeff = int(coeff) # should be valid base 10 integer
        i = term.find('x')
        if i == -1: x_exp = 0 # not present
        else:
            i += 1
            while i < len(term) and (term[i] in '0123456789'): i += 1
            x_exp = term[term.find('x')+1:i]
            if x_exp == '': x_exp = 1
            else: x_exp = int(x_exp)
        i = term.find('y')
        if i == -1: y_exp = 0
        else:
            i += 1
            while i < len(term) and (term[i] in '0123456789'): i += 1
            y_exp = term[term.find('y')+1:i]
            if y_exp == '': y_exp = 1
            else: y_exp = int(y_exp)
        if not ((x_exp,y_exp) in polymap): polymap[(x_exp,y_exp)] = 0
        polymap[(x_exp,y_exp)] += coeff
#        print('inserted (%d,%d)-->%d'%(x_exp,y_exp,coeff))
    return polymap

def mul_poly(p1,p2):
    prod = dict()
    for a in p1:
        for b in p2:
            k = (a[0]+b[0],a[1]+b[1])
            if not (k in prod): prod[k] = 0
            prod[k] += p1[a]*p2[b]
    for k in set(prod.keys()): # remove zeroes
        if prod[k] == 0: del prod[k]
    return prod

def sorter(a,b): # sort the x,y tuples as described
    if a[0] != b[0]: return b[0]-a[0] # decreasing x
    return a[1]-b[1] # increasing y

from functools import cmp_to_key
for line in sys.stdin:
    if line[0] == '#': break
    poly1 = preprocess_poly(line[:-1])
    poly2 = preprocess_poly(input())
#    print(poly1)
#    print(poly2)
    prod = mul_poly(poly1,poly2)
#    print('prod =',prod)
    l1 = '' # output lines
    l2 = ''
    first = True
    for k in sorted(prod.keys(),key=cmp_to_key(sorter)):
        if first:
            first = False
            if prod[k] == -1:
                l1 += ' '
                l2 += '-'
            elif prod[k] != 1:
                l1 += ' '*len(str(prod[k]))
                l2 += str(prod[k])
        else:
            if prod[k] < 0:
                l1 += '   '
                l2 += ' - '
                if prod[k] != -1:
                    l1 += ' '*len(str(abs(prod[k])))
                    l2 += str(abs(prod[k]))
            else:
                l1 += '   '
                l2 += ' + '
                if prod[k] != 1:
                    l1 += ' '*len(str(prod[k]))
                    l2 += str(prod[k])
        # print x and y
        if k == (0,0): # constant should include 1 if it is 1
            if abs(prod[k]) == 1:
                l1 += ' '
                l2 += '1'
        else:
            if k[0] != 0:
                l1 += ' '
                l2 += 'x'
                if k[0] != 1:
                    l1 += str(k[0])
                    l2 += ' '*len(str(k[0]))
            if k[1] != 0:
                l1 += ' '
                l2 += 'y'
                if k[1] != 1:
                    l1 += str(k[1])
                    l2 += ' '*len(str(k[1]))
    if l1 == '': print(' \n0') # nothing
    else: print(l1+'\n'+l2)

