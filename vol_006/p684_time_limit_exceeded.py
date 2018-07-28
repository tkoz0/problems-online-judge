
def det(M):
#    print('given',M)
    mult = 1 # what the determinant is multiplied by during operations
    for r in range(len(M)):
        if M[r][r] == 0: # swap in a row that starts with nonzero value
            sr = -1
            for rr in range(r+1,len(M)):
                if M[rr][r] != 0: sr = rr; break
            if sr == -1: return 0 # main diagonal will have 0
            mult *= -1 # swapping rows negates determinant
            M[r], M[sr] = M[sr], M[r]
        assert M[r][r] != 0
        # multiply all rows below that start with nonzero value
        # this ensures an integer multiple of row r can be subtracted
        for rr in range(r+1,len(M)):
            if M[rr][r] == 0: continue
            for cc in range(r,len(M)): M[rr][cc] *= M[r][r]
            mult *= M[r][r] # result of multiplying row by multiple
            submult = M[rr][r] // M[r][r]
            # adding row multiple doesnt change determinant
            for cc in range(r,len(M)): M[rr][cc] -= submult*M[r][cc]
            assert M[rr][r] == 0
#        print('step',M)
    determinant = 1
    for r in range(len(M)): determinant *= M[r][r]
    assert determinant % mult == 0
    return determinant // mult

while True:
    n = int(input())
    if n == 0: break
    assert n <= 30
    M = []
    for z in range(n): M.append(list(map(int,input().split())))
    print(det(M))
print('*')
