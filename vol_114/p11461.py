
limit = 100000
squares = []
d = 0
while d*d <= limit:
    squares.append(d*d)
    d += 1
squares.append(d*d) # guarantee a square larger than any inputs

def count(a,b):
    global squares
    alo, ahi = 0, len(squares)-1
    blo, bhi = 0, len(squares)-1
    while alo < ahi: # smallest square that is at least a
        mid = (alo+ahi)//2
        if squares[mid] >= a: ahi = mid
        else: alo = mid+1
#    if squares[alo] < a: alo += 1 # use 1 past end if none are in range
    while blo < bhi: # smallest square that is greater than b
        mid = (blo+bhi)//2
        if squares[mid] > b: bhi = mid
        else: blo = mid+1
#    if squares[blo] <= b: blo += 1 # use 1 past end if none are in range
    return blo-alo # excludes squares[blo]

while True:
    a, b = map(int,input().split())
    if a == 0 and b == 0: break
    assert 0 < a <= b <= 100000
    print(count(a,b))
