import sys

def match(card1,card2):
    return card1[0] == card2[0] or card1[1] == card2[1]

def move(piles):
    for i in range(1,len(piles)): # find a top card to move left 1 or 3 spaces
        if i >= 3 and match(piles[i-3][-1],piles[i][-1]): # try 3 first
            piles[i-3].append(piles[i][-1]) # move card
            piles[i].pop()
            if len(piles[i]) == 0: # remove empty pile
                piles.pop(i)
            return True
        if match(piles[i-1][-1],piles[i][-1]): # try 1 left
            piles[i-1].append(piles[i][-1])
            piles[i].pop()
            if len(piles[i]) == 0:
                piles.pop(i)
            return True
    return False # no move

for line in sys.stdin:
    if line[0] == '#': break
    deck = (line.split()+input().split())[::-1]
    piles = []
    while len(deck) > 0:
        piles.append([deck.pop()]) # put at end
        while move(piles): pass # perform moves as they exist
    print('%d pile%s remaining:'%(len(piles),'s' if len(piles) != 1 else ''),
        ' '.join(str(len(p)) for p in piles))
