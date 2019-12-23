
lower = 10000
upper = 6227020800

fac = [1]
while True: # factorials within limit
    fac.append(fac[-1]*len(fac))
    if fac[-1] > upper: fac.pop(); break

while True:
    try: n = int(input())
    except EOFError: break
#    assert n >= 0
    if n < 0: print(0); continue # ??? (due to wrong answer)
    if n >= len(fac): print('Overflow!')
    elif fac[n] < lower: print('Underflow!')
    else: print(fac[n])
