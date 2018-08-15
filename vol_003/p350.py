
case = 0
while True:
    case += 1
    Z, I, M, L = map(int,input().split())
    if Z == I == M == L == 0: break
#    assert 0 <= L < M <= 9999
    assert 0 <= L <= 9999
    assert 0 <= M <= 9999
    assert 0 <= Z <= 9999
    assert 0 <= I <= 9999
    index = [-1]*M # index in sequence (0...)
    if L < M: index[L] = 0
    else: # skip number that isnt in range of modulus
        L = (Z*L+I)%M
        index[L] = 1
    # Z*L+I (mod M) until cycle
    rand = L
    while True:
        randnew = (Z*rand+I)%M
        # cycle length is difference of indexes of 2 repeated numbers
        if index[randnew] != -1:
            print('Case %d: %d'%(case,1+index[rand]-index[randnew]))
            break
        index[randnew] = 1+index[rand]
        rand = randnew
