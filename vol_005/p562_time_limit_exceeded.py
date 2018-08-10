
num_cases = int(input())

for case in range(num_cases):
    m = int(input())
    assert m <= 100
    coins = list(map(int,input().split()))
    assert len(coins) == m
    coinssum = sum(coins)
    possible = [False]*(1+coinssum) # index i is whether i cents can be formed
    possible[0] = True
    for c in coins:
        i = coinssum - c
        # if i cents is possible with coins before c then i+c cents is possible
        # go backwards so current coin isnt considered in any True assignments
        while i >= 0:
            if possible[i]: possible[i+c] = True
            i -= 1
    # if i cents is formed, coinssum-i cents is guaranteed formable as well
    print(min(abs(coinssum-2*i) for i in range(1+coinssum) if possible[i]))
