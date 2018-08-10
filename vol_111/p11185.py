
digits = '012'

while True:
    N = int(input())
    if N < 0: break
    if N == 0: print('0'); continue # special case
    b3 = ''
    while N != 0:
        b3 += digits[N % 3]
        N //= 3
    print(b3[::-1]) # little endian to big endian
