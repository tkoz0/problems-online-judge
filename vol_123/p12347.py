import sys

pre = [int(z) for z in sys.stdin]

def post(beg,end): # subtree in range [beg,end) in array pre
    global pre
    if beg == end: return # empty subtree
    mid = beg+1 # find middle to split into left and right subtrees
    # this assumes the preorder given is valid
    while mid < end and pre[mid] < pre[beg]: mid += 1
    # mid is now end or first index with value larger than pre[beg] (root)
    post(beg+1,mid) # print subtrees first
    post(mid,end)
    print(pre[beg]) # print value after subtrees (post ordering)

post(0,len(pre))
