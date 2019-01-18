
case = 0
while True:
    case += 1
    n = int(input())
    if n == 0: break
    assert 1 < n <= 1000
    nums = []
    for _ in range(n):
        nums.append(int(input()))
    m = int(input())
    assert 0 < m < 25

    # find all possible sums
    nums = set(nums)
    sums = set()
    for z1 in nums:
        for z2 in nums:
            if z1 != z2: sums.add(z1+z2)
    sums = sorted(sums) # sort for binary searching

    print('Case %d:'%case)

    for _ in range(m): # process queries
        query = int(input())
        # binary search for near number
        lo, hi = 0, len(sums)-1
        while lo != hi:
            mid = (lo+hi)//2 # split into [lo,mid] and [mid+1,hi]
            if query <= sums[mid]:
                hi = mid
            else: lo = mid+1
        # will be either sums[lo] or sums[lo+1] or sums[lo-1]
        # sums[lo] is the largest value that is <= query
        closest = sums[lo]
        if lo+1<len(sums) and abs(sums[lo+1]-query) < abs(query-closest):
            closest = sums[lo+1] # has smaller absolute difference
        if lo>0 and abs(query-sums[lo-1]) < abs(query-closest):
            closest = sums[lo-1] # has smaller absolute difference
        print('Closest sum to %d is %d.'%(query,closest))

