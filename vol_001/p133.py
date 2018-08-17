
class node:
    def __init__(self,z):
        self.l = None
        self.r = None
        self.n = z

def do_step(ccw,cw,k,m,seq):
    # take steps
    for z in range(k-1): ccw = ccw.r
    for z in range(m-1): cw = cw.l
    if cw == ccw: # selected same person
        ret = (cw.n,)
        if cw.l == cw: # last node in list, destroy list
            ccw, cw = None, None
        else:
            ccw = ccw.r # advance to next
            cw = cw.l
            n = cw.r # remove the 1
            n.l.r = n.r
            n.r.l = n.l
        seq.append(ret)
    else: # selected 2 different people
        ret = (ccw.n,cw.n)
        if cw.l.l == cw: # last 2 in list, destroy list
            ccw, cw = None, None
        else: # advance to next, skip other selected node
            ocw, occw = cw, ccw # originals
            ccw = ccw.r # advance, skip nodes to remove
            while ccw == ocw or ccw == occw: ccw = ccw.r
            cw = cw.l
            while cw == ocw or cw == occw: cw = cw.l
            # remove originals
            ocw.l.r = ocw.r
            ocw.r.l = ocw.l
            occw.l.r = occw.r
            occw.r.l = occw.l
        seq.append(ret)
    return (ccw,cw)

while True:
    N, k, m = map(int,input().split())
    if N == k == m == 0: break
    assert k > 0 # counter clockwise (1,2,...)
    assert m > 0 # counterclockwise (N,N-1,...)
    assert 0 < N < 20
    # make a cyclic list
    ccw = node(1) # go to .r (k)
    cw = ccw # go to .l (m)
    for z in range(2,N+1):
        cw.r = node(z) # insert new node
        cw.r.l = cw
        cw = cw.r # move to next (end)
    ccw.l = cw # link list cyclically
    cw.r = ccw
    num_taken = 0
    seq = [] # tuples for each 1 or 2 people removed at each step
    while not (cw is None): # set none when list empty
        ccw, cw = do_step(ccw,cw,k,m,seq)
    print(','.join(''.join(('%3d'%u) for u in t) for t in seq))
