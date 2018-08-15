import math

while True:
    try: n = int(input())
    except EOFError: break
    # problem is nonsense, positive values are sensible
    # 0-7 is underflow, 8-13 is okay, 14+ is overflow
    # for negatives, F(0)=0*F(-1) --> F(-1) = F(0)/0 = infinity (the nonsense)
    # therefore "negative odd = overflow, negative even = underflow"
    if n < 0:
        if n % 2 == 0: print('Underflow!')
        else: print('Overflow!')
    elif 0 <= n <= 7: print('Underflow!')
    elif 8 <= n <= 13: print(math.factorial(n))
    else:
        assert n >= 14
        print('Overflow!')
