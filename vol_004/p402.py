import sys

counter = 0
for line in sys.stdin:
    counter += 1
    deck = list(map(int,line.split()))
    N = deck[0]
    X = deck[1]
    deck = deck[2:]
    assert 1 <= N <= 50 and 1 <= X <= N
    people = list(range(1,N+1))
    for card in deck:
        i = 0
        while True:
            if len(people) <= X: break # number of required people
            i += card-1 # steps of card-1 since people are being erased
            if len(people) <= X or i >= len(people): break
            people.pop(i)
    print('Selection #%d' % counter)
    print(' '.join(str(p) for p in people))
    print()
