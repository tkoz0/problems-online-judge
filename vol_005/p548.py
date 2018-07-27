import sys

class node:
    def __init__(self,val):
        self.l = None
        self.r = None
        self.v = val

LNR, LRN, LNRtable = [], [], dict()

def make_tree(lnrlo,lnrhi,lrnlo,lrnhi):
    global LNR, LRN, LNRtable
    assert lnrhi-lnrlo == lrnhi-lrnlo # same size sets of nodes to work with
    if lnrlo == lnrhi: return None # no nodes in subtree
    tree = node(LRN[lrnhi-1]) # last in LRN in N, root of this subtree
    i = LNRtable[tree.v] # split LNR order for left and right subtrees
    assert lnrlo <= i < lnrhi
    ls, rs = i-lnrlo, lnrhi-i-1 # sizes of each subtree
    tree.l = make_tree(lnrlo,i,lrnlo,lrnlo+ls)
    tree.r = make_tree(i+1,lnrhi,lrnhi-rs-1,lrnhi-1)
    return tree

def process_tree(tree): # dynamic approach to finding min sum path
    if tree is None: return None
    # min subtree sum, leaf value on path
    if tree.l is None and tree.r is None: return (tree.v,tree.v)
    L, R = process_tree(tree.l), process_tree(tree.r)
    # only 1 subtree, add tree value to return value, remember leaf node
    if L is None: return (R[0]+tree.v,R[1])
    if R is None: return (L[0]+tree.v,L[1])
    # pick best of the 2 subtrees
    if L[0] < R[0]: return (L[0]+tree.v,L[1])
    if R[0] < L[0]: return (R[0]+tree.v,R[1])
    if L[1] < R[1]: return (L[0]+tree.v,L[1])
    return (R[0]+tree.v,R[1])

for line in sys.stdin:
    LNR = list(map(int,line.split())) # in order
    LRN = list(map(int,input().split())) # post order
    assert len(LNR) == len(LRN)
    # make hash table to quickly find numbers in LNR (the N somewhere in middle)
    LNRtable = dict() # maps value to index in LNR
    for i,v in enumerate(LNR):
        assert not (v in LNRtable) # numbers are not duplicated
        LNRtable[v] = i
    tree = make_tree(0,len(LNR),0,len(LRN))
    print(process_tree(tree)[1])
