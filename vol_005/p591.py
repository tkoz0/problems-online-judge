
setnum = 0
while True:
    setnum += 1
    n = int(input())
    if n == 0: break
    assert 1 <= n <= 50
    stacks = list(map(int,input().split()))
    blocks = sum(stacks)
    assert blocks % n == 0
    # move all blocks above what the final average height will be
    avght = blocks // n
    moved = 0
    for h in stacks:
        if h > avght: moved += h - avght
    print('Set #%d'%setnum)
    print('The minimum number of moves is %d.'%moved)
    print()
