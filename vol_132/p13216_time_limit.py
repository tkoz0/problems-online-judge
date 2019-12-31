
T = int(input())
assert 1 <= T <= 5000

pow66 = [(66**i)%100 for i in range(10)]

for _ in range(T):
    n = input() # dont convert to int, relatively slow for big integers
    assert 1 <= len(n) <= 1001 # 1001 to allow for 10^1000
    assert n.isdigit()
    n = n[::-1] # "little endian"
    result = 1
    base = None # similar to exponentiation by squaring but in base 10
    for p,d in enumerate(n): # p for power, d for digit
        if p == 0: base = 66
        else: base = (base**10) % 100
        result = (result*(base**int(d)))%100
    print(result)
