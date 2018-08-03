import sys

def flip(stack,i): stack[i:] = reversed(stack[i:])

def flips(stack):
    seq = [] # sequence of flips to sort stack (largest first)
    nexti = 0 # index to move maximum from substack
    while nexti < len(stack):
        maxi = nexti
        for i in range(nexti+1,len(stack)):
            if stack[i] > stack[maxi]: maxi = i
        if maxi == nexti: nexti += 1; continue
        if maxi == len(stack)-1: # 1 flip to move maximum to nexti
            flip(stack,nexti)
            seq.append(nexti)
        else: # flip to get max to top, then flip to right position
            flip(stack,maxi)
            flip(stack,nexti)
            seq.append(maxi)
            seq.append(nexti)
        nexti += 1
    return seq

for line in sys.stdin:
    pancakes = list(map(int,line.split()))[::-1]
    assert 1 <= len(pancakes) <= 30
    print(line,end='')
    seq = flips(pancakes)
    for i in seq: print(i+1,' ',sep='',end='')
    print(0)
