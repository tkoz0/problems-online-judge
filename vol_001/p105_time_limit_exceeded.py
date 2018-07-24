import sys

hm = [] # height map
for line in sys.stdin:
    l,h,r = map(int,line.split())
    assert l < 10000 and r < 10000
    # expand height map to have space for all buildings
    while len(hm) < r: hm.append(0)
    for i in range(l,r): hm[i] = max(hm[i],h) # pick highest building

i = 0
while i < len(hm):
    j = i+1 # find where height changes
    while j < len(hm) and hm[i] == hm[j]: j += 1
    if j == len(hm): break # reached end
    if hm[j] < hm[i]: # height drops, use j-1 index
        print(j-1,' ',hm[j],' ',sep='',end='')
    else: print(j,' ',hm[j],' ',sep='',end='') # height increases
    i = j
# last vertical line position, 0 for horizental after that
print(len(hm),0)
