import sys

def fits_in(a,b): # box a fits in box b
    a, b = a[0], b[0] # reference the list of box dimensions
    for i in range(len(a)):
        if a[i] >= b[i]: return False
    return True

for beginline in sys.stdin:
    beginline = list(map(int,beginline[:-1].split()))
    k, n = beginline[0], beginline[1] # num boxes, dimensionality
    assert 1 <= n <= 10 and 1 <= k <= 30
    boxes = []
    # read k boxes, save as sorted lists of integers, include box number
    for z in range(k):
        boxline = sys.stdin.readline()[:-1] # ignore \n
        boxline = sorted(map(int,boxline.split()))
        boxes.append((boxline,z+1))
    # by sorting, nesting only goes forward in indexing
    boxes = sorted(boxes)
    nest = [] # generate nesting table, box[i][j] is whether box i fits in box j
    for b1 in range(k):
        nest.append([])
        for b2 in range(k): nest[b1].append(fits_in(boxes[b1],boxes[b2]))
    # use dynamic programming, it is solving a directed acyclic graph
    # longest[i] means starting at boxes[i], longest nest sequence
    # uses indexes in boxes list
    longest = list([] for z in range(k))
    for start in range(k-1,-1,-1):
        longest[start].append(start) # sequence starts with current box
        nexti = start # find index of optimal next nesting box
        for boxi in range(start+1,k):
            if not nest[start][boxi]: continue # must nest to consider it
            # first possible optimal sequence after start
            if nexti == start: nexti = boxi
            # already found one possibility, compare lengths
            elif len(longest[boxi]) > len(longest[nexti]): nexti = boxi
            elif len(longest[boxi]) == len(longest[nexti]):
                # pick path with smaller box id for minimum lexicographic order
                if boxes[boxi][1] < boxes[nexti][1]: nexti = boxi
        # found a longest following nesting sequence
        if nexti != start: longest[start] += longest[nexti]
    start = 0 # find longest
    for i in range(1,k):
        if len(longest[i]) > len(longest[start]): start = i
    # print box numbers and information
    print(len(longest[start]))
    print(boxes[longest[start][0]][1],end='')
    for boxi in longest[start][1:]:
        print(' ',boxes[boxi][1],sep='',end='')
    print()
