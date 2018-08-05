
while True:
    l = int(input())
    if l == 0: break
    n = int(input())
    assert l < 1000
    assert n < 50
    case_infinity = l*l # cost can never exceed this
    cuts = list(map(int,input().split())) # increasing order
    assert len(cuts) == n
    cuts = [0]+cuts+[l] # include endpoints
    memo = dict()
    for i in range(1,len(cuts)): # end pieces, no cost, "recursion base"
        memo[(cuts[i-1],cuts[i])] = 0
    for cutsbetween in range(2,len(cuts)):
        beg = 0
        end = cutsbetween
        while end < len(cuts):
            min_cost = case_infinity # min cost to cut split "halves" here
            for cut in range(beg+1,end): # where to make cut
                min_cost = min(min_cost,memo[(cuts[beg],cuts[cut])]+memo[(cuts[cut],cuts[end])])
            # add cost to cut current piece
            memo[(cuts[beg],cuts[end])] = cuts[end]-cuts[beg] + min_cost
            beg += 1
            end += 1
    print('The minimum cutting is %d.'%memo[(0,l)])
