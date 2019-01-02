
n = int(input())

for _ in range(n):
    d = [input().split(),input().split(),input().split()]
    thiscase = 0
    for c in 'ABCDEFGHIJKL':
        # try c is light
        light = True
        for w in d:
            L = 0 if c in w[0] else 1
            R = 0 if c in w[1] else 1
            if w[2] == 'even' and L != R: light = False
            if w[2] == 'up' and L <= R: light = False
            if w[2] == 'down' and L >= R: light = False
        # try c is heavy
        heavy = True
        for w in d:
            L = 1 if c in w[0] else 0
            R = 1 if c in w[1] else 0
            if w[2] == 'even' and L != R: heavy = False
            if w[2] == 'up' and L <= R: heavy = False
            if w[2] == 'down' and L >= R: heavy = False
        if light:
            print(c,'is the counterfeit coin and it is light.')
            thiscase += 1
        if heavy:
            print(c,'is the cointerfeit coin and it is heavy.')
            thiscase += 1
    assert thiscase == 1

quit()

for _ in range(n):
    definite_real = set()
    possible_fake = set()
    L1, R1, B1 = input().split() # 3 weighings
    L2, R2, B2 = input().split()
    L3, R3, B3 = input().split()
    assert len(L1) == len(R1) # same coins on each side
    assert len(L2) == len(R2)
    assert len(L3) == len(R3)
    assert len(set(L1+R1)) == len(L1)+len(R1) # distinct coins per weighing
    assert len(set(L2+R2)) == len(L2)+len(R2)
    assert len(set(L3+R3)) == len(L3)+len(R3)
    if B1 == 'even' and B2 == 'even' and B3 == 'even': assert 0
    if B1 == 'even': definite_real |= set(L1+R1) # known real, same weight
    else: possible_fake |= set(L1+R1) # unequal weight so maybe fake
    if B2 == 'even': definite_real |= set(L2+R2)
    else: possible_fake |= set(L2+R2)
    if B3 == 'even': definite_real |= set(L3+R3)
    else: possible_fake |= set(L3+R3)
    possible_fake -= definite_real # limit possibilities
    assert len(possible_fake) > 0
    consistent = [] # possible fakes that are consistent with enqual weighings
    # store as tuples (coin,heavy boolean)
    for coin in sorted(possible_fake):
        # coin only appeared in unbalanced case(s)
        heavy = [] # whether its heavy
        if B1 != 'even':
            if coin in L1: heavy.append(B1 == 'up')
            if coin in R1: heavy.append(B1 == 'down')
        if B2 != 'even':
            if coin in L2: heavy.append(B2 == 'up')
            if coin in R2: heavy.append(B2 == 'down')
        if B3 != 'even':
            if coin in L3: heavy.append(B3 == 'up')
            if coin in R3: heavy.append(B3 == 'down')
        if len(set(heavy)) == 1:
            consistent.append((coin,heavy[0]))
    assert len(consistent) > 0
#    if len(consistent) == 1: # found fake
    print('%s is the counterfeit coin and it is %s.'%(consistent[0][0],
        'heavy' if consistent[0][1] else 'light'))

