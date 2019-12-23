
N = int(input())

# tree consists of nested lists
# [x,x,x,x] to split (p), otherwise 'e' or 'f' for empty/full

def make_tree(s,i):
    if s[i] != 'p': return (s[i],i+1) # subtree value, next index to use
    result = [None]*4 # split for p
    result[0], i = make_tree(s,i+1)
    result[1], i = make_tree(s,i)
    result[2], i = make_tree(s,i)
    result[3], i = make_tree(s,i)
    return (result,i)

def count(T,s): # counts black pixels
    if T == 'f': return s*s
    if T == 'e': return 0
    return sum(count(T[i],s//2) for i in range(4))

# image nodes, square side length
def black(A,B,s):
    if A == 'f' or B == 'f': return s*s # full if at least 1 is full
    if A == 'e': return count(B,s)
    if B == 'e': return count(A,s)
    return sum(black(A[i],B[i],s//2) for i in range(4))

for _ in range(N):
    A = make_tree(input(),0)[0]
    B = make_tree(input(),0)[0]
    print('There are',black(A,B,32),'black pixels.')
