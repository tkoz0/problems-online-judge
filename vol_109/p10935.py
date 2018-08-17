
while True:
    n = int(input())
    assert n <= 50
    if n <= 0: break
    deck = list(range(1,n+1)) # last is top
    seq = []
    throwfirst = True
    while len(deck) != 1:
        if throwfirst:
            if len(deck) % 2 == 1: throwfirst = False
            seq += deck[0::2]
            deck = deck[1::2]
        else:
            if len(deck) % 2 == 1: throwfirst = True
            seq += deck[1::2]
            deck = deck[0::2]
    if len(seq) != 0:
        print('Discarded cards:',', '.join(str(z) for z in seq))
    else: print('Discarded cards:')
    print('Remaining card:',deck[0])
