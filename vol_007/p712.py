
tree_num = 0
while True:
    tree_num += 1
    n = int(input()) # S-tree depth
    if n == 0: break
    assert 1 <= n <= 7
    order = list(int(x[1:]) for x in input().split())
    assert len(order) == n
    assert len(set(order)) == n # all values are unique
    terminal = list(map(int,list(input())))
    assert len(terminal) == 2**n
    m = int(input()) # number of VVAs
    print('S-Tree #%d:'%tree_num)
    fvals = [] # list computed function values
    inorder = [0]*n
    for z in range(m):
        vva = list(map(int,list(input()))) # order x1,x2,...
        # map these to give the order with the tree variable ordering
        for o in range(n): inorder[o] = vva[order[o]-1] # 1..n to 0..n-1 index
        tnum = 0 # binary value of this is index in terminal nodes
        for b in inorder: tnum = 2*tnum + b
        fvals.append(terminal[tnum])
    print(''.join(str(z) for z in fvals))
    print()
