
case = 0
while True:
    case += 1
    N1, N2 = map(int,input().split())
    if N1 == N2 == 0: break
    assert 1 <= N1 <= 100
    assert 1 <= N2 <= 100
    print('Twin Towers #%d'%case)
    t1 = list(map(int,input().split()))
    t2 = list(map(int,input().split()))
    assert len(t1) == N1
    assert len(t2) == N2
    row = [0]*(N1+1) # row of longest common subsequence table
    for i,n in enumerate(t2):
        newrow = [0]*(N1+1)
        for j,nn in enumerate(t1):
            if nn == n: newrow[j+1] = 1+row[j]
            else: newrow[j+1] = max(newrow[j],row[j+1])
        row = newrow
    print('Number of Tiles : %d\n'%row[-1])
