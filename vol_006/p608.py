
n = int(input())
assert n > 0

for _ in range(n): # each test case
    data = [input().split(),input().split(),input().split()]
    thiscase = 0 # times a result was found
    counterfeit = ''

    # reduce possibilities
    definite_real = set() # if scale is even
    possible_fake = set() # if scale is not even
    for result in data:
        if result[2] == 'even': definite_real |= set(result[0]+result[1])
        else: possible_fake |= set(result[0]+result[1])
    possible_fake -= definite_real

    for coin in possible_fake:
        # assume coin is light
        light = True
        for result in data:
            L, R = 0, 0 # weights, subtract 1 for side coin is on
            if coin in result[0]: L -= 1
            if coin in result[1]: R -= 1

            # check from another solution
#            LL = -1 if (coin in result[0]) else 0
#            RR = -1 if (coin in result[1]) else 0
#            assert L == LL and R == RR, '%d %d %d %d'%(L,LL,R,RR)

            if result[2] == 'even' and L != R: light = False; break
            if result[2] == 'up' and R >= L: light = False; break
            if result[2] == 'down' and L >= R: light = False; break
        # assume coin in heavy
        heavy = True
        for result in data:
            L, R = 0, 0 # weights, add 1 for side coin is on
            if coin in result[0]: L += 1
            if coin in result[1]: R += 1

            # check from another solution
#            LL = 1 if (coin in result[0]) else 0
#            RR = 1 if (coin in result[1]) else 0
#            assert L == LL and R == RR, '%d %d %d %d'%(L,LL,R,RR)

            if result[2] == 'even' and L != R: heavy = False; break
            if result[2] == 'up' and R >= L: heavy = False; break
            if result[2] == 'down' and L >= R: heavy = False; break
        if light:
            print(coin,'is the counterfeit coin and it is light.')
            thiscase += 1
            counterfeit = coin[:]
        if heavy:
            print(coin,'is the counterfeit coin and it is heavy.')
            thiscase += 1
            counterfeit = coin[:]
    assert thiscase == 1 # result should be uniquely found by brute force
