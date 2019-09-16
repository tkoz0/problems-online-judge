import math
sets = int(input())
eps = 0.000001 # error allowed

def assert_triangle(a,A,b,B,c,C):
    assert a and A and b and B and c and C # non null
    assert A >= eps and B >= eps and C >= eps # positive angles
    assert a >= eps and b >= eps and c >= eps # positive sides
    assert abs(math.pi-A-B-C) < eps # angles sum to pi
    sa, sb, sc = a/math.sin(A), b/math.sin(B), c/math.sin(C) # law of sines
    assert abs(sa-sb) < eps and abs(sa-sc) < eps and abs(sb-sc) < eps
    assert abs(a-b*math.cos(C)-c*math.cos(B)) < eps # side length
    assert abs(b-a*math.cos(C)-c*math.cos(A)) < eps
    assert abs(c-a*math.cos(B)-b*math.cos(A)) < eps
    assert abs(a*a-b*b-c*c+2.0*b*c*math.cos(A)) < eps # law of cosines
    assert abs(b*b-a*a-c*c+2.0*a*c*math.cos(B)) < eps
    assert abs(c*c-a*a-b*b+2.0*a*b*math.cos(C)) < eps
    # law of tangents
    assert abs((a-b)/(a+b)-math.tan((A-B)/2.0)/math.tan((A+B)/2.0)) < eps
    assert abs((a-c)/(a+c)-math.tan((A-C)/2.0)/math.tan((A+C)/2.0)) < eps
    assert abs((b-c)/(b+c)-math.tan((B-C)/2.0)/math.tan((B+C)/2.0)) < eps
    # heron's formula and area
    s = (a+b+c)/2.0
    assert a+b > c and a+c > b and b+c > a # length inequality
    area = math.sqrt(s*(s-a)*(s-b)*(s-c))
    a1, a2, a3 = 0.5*a*b*math.sin(C), 0.5*a*c*math.sin(B), 0.5*b*c*math.sin(A)
    assert abs(a1-a2) < eps and abs(a1-a3) < eps and abs(a2-a3) < eps
    assert abs(area-a1) < eps and abs(area-a2) < eps and abs(area-a3) < eps

def print_t(a,A,b,B,c,C):
    print('%.6f %.6f %.6f %.6f %.6f %.6f'%(a,A,b,B,c,C))

for _ in range(sets):
    a, A, b, B, c, C = map(float,input().split())
    if a == -1.0: a = None
    if A == -1.0: A = None
    if b == -1.0: b = None
    if B == -1.0: B = None
    if c == -1.0: c = None
    if C == -1.0: C = None
    if (a and a < eps) or (A and A < eps) or (b and b < eps) \
        or (B and B < eps) or (c and c < eps) or (C and C < eps):
        print('Invalid input.');#print(1) # values not positive
    else: # all inputs positive
        if (A and B) or (A and C) or (B and C): # 2 or 3 angles known
            if not A: A = math.pi-B-C
            if not B: B = math.pi-A-C
            if not C: C = math.pi-A-B
            if A < eps or B < eps or C < eps: # angles should be positive
                print('Invalid input.');#print(2)
            else:
                if abs(math.pi-A-B-C) < eps: # angles should sum to pi
                    if a or b or c: # need to know a side length
                        if a: m = a/math.sin(A) # law of sines
                        if b: m = b/math.sin(B)
                        if c: m = c/math.sin(C)
                        if not a: a = m*math.sin(A)
                        if not b: b = m*math.sin(B)
                        if not c: c = m*math.sin(C)
                        try:
                            assert_triangle(a,A,b,B,c,C)
                            print_t(a,A,b,B,c,C)
                        except AssertionError: print('Invalid input.');#print(3)
                    else: print('Invalid input.');#print(4)
                else: print('Invalid input.');#print(5)
        else: # 1 or 0 angles known
            if A or B or C: # 1 angle is known
                if A and b and c: # 2 adjacent sides known, compute 3rd
                    if not a: a = math.sqrt(b*b+c*c-2.0*b*c*math.cos(A))
                    m = math.sin(A)/a # for law of sines
                elif B and a and c:
                    if not b: b = math.sqrt(a*a+c*c-2.0*a*c*math.cos(B))
                    m = math.sin(B)/b
                elif C and a and b:
                    if not c: c = math.sqrt(a*a+b*b-2.0*a*b*math.cos(C))
                    m = math.sin(C)/c
                if a and b and c: # 3rd side computed or given
# TODO see if an improper given 3rd side can mess this up
                    if A: # compute smaller angle first (<pi/2 radians)
                        if b < c: B = math.asin(b*m)
                        else: C = math.asin(c*m)
                    elif B:
                        if a < c: A = math.asin(a*m)
                        else: C = math.asin(c*m)
                    elif C:
                        if a < b: A = math.asin(a*m)
                        else: B = math.asin(b*m)
                    if not A: A = math.pi-B-C # compute last angle
                    if not B: B = math.pi-A-C
                    if not C: C = math.pi-A-B
                    try:
                        assert_triangle(a,A,b,B,c,C)
                        print_t(a,A,b,B,c,C)
                    except AssertionError: print('Invalid input.');#print(6)
                else: # cases based on which sides are known (need 2)
                    two_solutions = False # set to true if arcsin is not pi/2
                    if a and b:
                        if a and A:
                            B = b*math.sin(A)/a
                            if abs(math.pi/2.0-B) > eps: two_solutions = True
                        else:
                            A = a*math.sin(B)/b
                            if abs(math.pi/2.0-A) > eps: two_solutions = True
                    elif a and c:
                        if a and A:
                            C = c*math.sin(A)/a
                            if abs(math.pi/2.0-C) > eps: two_solutions = True
                        else:
                            A = a*math.sin(C)/c
                            if abs(math.pi/2.0-A) > eps: two_solutions = True
                    elif b and c:
                        if b and B:
                            C = c*math.sin(B)/b
                            if abs(math.pi/2.0-C) > eps: two_solutions = True
                        else:
                            B = b*math.sin(C)/c
                            if abs(math.pi/2.0-B) > eps: two_solutions = True
                    if two_solutions: print('Invalid input.');#print(10)
                    if (A and B) or (A and C) or (B and C): # 2 angles success
                        if not A: A = math.pi-B-C # compute 3rd angle
                        if not B: B = math.pi-A-C
                        if not C: C = math.pi-A-B
                        if not a: a = b*math.sin(A)/math.sin(B) # 3rd side
                        if not b: b = a*math.sin(B)/math.sin(A)
                        if not c: c = a*math.sin(C)/math.sin(A)
                        try:
                            assert_triangle(a,A,b,B,c,C)
                            print_t(a,A,b,B,c,C)
                        except AssertionError:
                            print('Invalid input.');#print(12)
                    else: print('Invalid input.');#print(11)
            else: # no angles, need 3 side lengths
                if a+b > c and a+c > b and b+c > a: # triangle inequalities
                    if a and b and c: # have all 3, use law of cosines
                        if not A: A = math.acos((b*b+c*c-a*a)/(2.0*b*c))
                        if not B: B = math.acos((a*a+c*c-b*b)/(2.0*a*c))
                        if not C: C = math.acos((a*a+b*b-c*c)/(2.0*a*b))
                        try:
                            assert_triangle(a,A,b,B,c,C)
                            print_t(a,A,b,B,c,C)
                        except AssertionError: print('Invalid input.');#print(7)
                    else: print('Invalid input.');#print(8)
                else: print('Invalid input.');#print(9)
