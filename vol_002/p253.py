import sys

def rotable(a,b): # if strings of 4 chars are rotations of each other
    for i in range(4):
        a = a[1:]+a[0]
        if a == b: return True
    return False

def same(A,B):
    # determine if A can be rotated to be the same as B
    # move the position of A[1] face and check that everything matches
    A_rot = A[2]+A[4]+A[5]+A[3]
    if A[1] == B[1] and A[6] == B[6] and \
        rotable(A_rot,B[2]+B[4]+B[5]+B[3]): return True
    if A[1] == B[2] and A[6] == B[5] and \
        rotable(A_rot,B[4]+B[1]+B[3]+B[6]): return True
    if A[1] == B[3] and A[6] == B[4] and \
        rotable(A_rot,B[2]+B[1]+B[5]+B[6]): return True
    if A[1] == B[4] and A[6] == B[3] and \
        rotable(A_rot,B[2]+B[6]+B[5]+B[1]): return True
    if A[1] == B[5] and A[6] == B[2] and \
        rotable(A_rot,B[1]+B[4]+B[6]+B[3]): return True
    if A[1] == B[6] and A[6] == B[1] and \
        rotable(A_rot,B[2]+B[3]+B[5]+B[4]): return True
    return False

for line in sys.stdin:
    A = '.'+line[:6] # '.' so indexing can be done 1-6 instead of 0-5
    B = '.'+line[6:12]
    print(str(same(A,B)).upper())
