import sys

n = int(input())
assert 0 < n < 25

piles = list([i] for i in range(n)) # block world

def find(x): # return (pile number, index in pile)
    global piles
    for i,pile in enumerate(piles):
        for j,block in enumerate(pile):
            if block == x: return (i,j)
    assert 0 # should always find the block

def above_to_original(pos): # returns blocks above this to original positions
    global piles
    for block in piles[pos[0]][1+pos[1]:]: piles[block].append(block)
    piles[pos[0]] = piles[pos[0]][:1+pos[1]]

def move_onto(a,b): # above to original, then move a on top of b
    global piles
    pa, pb = find(a), find(b)
    if pa[0] == pb[0]: return # same pile, do nothing
    above_to_original(pa)
    above_to_original(pb)
    piles[pb[0]].append(piles[pa[0]].pop())

def move_over(a,b): # above a to original, then a on top of pile with b
    global piles
    pa, pb = find(a), find(b)
    if pa[0] == pb[0]: return # same pile, do nothing
    above_to_original(pa)
    piles[pb[0]].append(piles[pa[0]].pop())

def pile_onto(a,b): # above b to original, a and above on top of pile with b
    global piles
    pa, pb = find(a), find(b)
    if pa[0] == pb[0]: return # same pile, do nothing
    above_to_original(pb)
    piles[pb[0]] += piles[pa[0]][pa[1]:]
    piles[pa[0]] = piles[pa[0]][:pa[1]]

def pile_over(a,b): # a and above on top of pile with b
    global piles
    pa, pb = find(a), find(b)
    if pa[0] == pb[0]: return # same pile, do nothing
    piles[pb[0]] += piles[pa[0]][pa[1]:]
    piles[pa[0]] = piles[pa[0]][:pa[1]]

def print_world():
    for i,pile in enumerate(piles):
        print(i,':',sep='',end='')
        for block in pile: print(' ',block,sep='',end='')
        print()

for cmd in sys.stdin: # process each command
    cmd = cmd[:-1].split() # do not include new line char
    if cmd[0] == 'quit': break # end of input
    a = int(cmd[1])
    b = int(cmd[3])
    if a == b: continue # blocks must be different
    if cmd[0] == 'move':
        if cmd[2] == 'onto':
            move_onto(a,b)
        else:
            assert cmd[2] == 'over'
            move_over(a,b)
    else:
        assert cmd[0] == 'pile'
        if cmd[2] == 'onto':
            pile_onto(a,b)
        else:
            assert cmd[2] == 'over'
            pile_over(a,b)
print_world()
