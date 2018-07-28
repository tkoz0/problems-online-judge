import sys

case = 0
for line in sys.stdin:
    case += 1
    A, L = map(int,line.split())
    if A<0 and L<0: break # after last case
    terms = 1
    num = A
    while num != 1 and num <= L:
        num = (num//2 if num%2==0 else 3*num+1)
        if num <= L: terms += 1
    print('Case %d: A = %d, limit = %d, number of terms = %d'%(case,A,L,terms))
