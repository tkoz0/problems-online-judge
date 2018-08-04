
currency = [10000,5000,2000,1000,500,200,100,50,20,10,5]
currency = sorted(list(c//5 for c in currency)) # count in multiples of 5

ways = [0]*(1+30000//5)
ways[0] = 1
for c in currency: # dynamic programming
    for i in range(c,1+30000//5): ways[i] += ways[i-c]

while True:
    amount = float(input())
    if amount == 0.0: break
    originalamount = amount
    amount = int(round(amount*100.0))
    assert amount % 5 == 0
    print('%6.2f%17d'%(originalamount,ways[amount//5]))
