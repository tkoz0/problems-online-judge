
n = int(input())
assert n > 0

for _ in range(n): # each test case
    data = [input().split(),input().split(),input().split()]
    thiscase = 0 # times a result was found
    for coin in 'ABCDEFGHIJKL':
        # assume coin is light
        light = True
        for result in data:
            L, R = 0, 0 # weights, subtract 1 for side coin is on
            if coin in result[0]: L -= 1
            if coin in result[1]: R -= 1
            if result[2] == 'even' and L != R: light = False; break
            if result[2] == 'up' and R >= L: light = False; break
            if result[2] == 'down' and L >= R: light = False; break
        # assume coin in heavy
        heavy = True
        for result in data:
            L, R = 0, 0 # weights, add 1 for side coin is on
            if coin in result[0]: L += 1
            if coin in result[1]: R += 1
            if result[2] == 'even' and L != R: heavy = False; break
            if result[2] == 'up' and R >= L: heavy = False; break
            if result[2] == 'down' and L >= R: heavy = False; break
        if light:
            print(coin,'is the counterfeit coin and it is light.')
            thiscase += 1
        if heavy:
            print(coin,'is the counterfeit coin and it is heavy.')
            thiscase += 1
    assert thiscase == 1

