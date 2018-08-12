
def recurse(nums,l,i): # i is next num index to pick, l is list of nums to print
    if len(l) == 6: # base
        print(' '.join(str(z) for z in l))
    else:
        # ensure enough numbers remain
        for j in range(i,1+len(nums)-(6-len(l))):
            l.append(nums[j])
            recurse(nums,l,j+1)
            l.pop() # backtrack

first = True
while True:
    line = list(map(int,input().split()))
    if line[0] == 0: break
    nums = line[1:]
    k = line[0]
    assert 6 < k < 13
    assert k == len(nums)
    if not first: print()
    recurse(nums,[],0)
    first = False
