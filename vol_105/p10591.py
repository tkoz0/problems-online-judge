import math

def compute_end89(i):
    assert i > 0
    while True:
        if i == 1: return False
        elif i == 89: return True
        s = 0
        while i != 0:
            i, d = divmod(i,10)
            s += d*d
        i = s

# all sequences reach 1 or 89 (see project euler #92)
limit = 10**9
# 2nd in any sequence will be at most 9^2 * (most digits)
end89 = [False]*(1+81*math.ceil(math.log10(limit)))
for i in range(1,len(end89)): end89[i] = compute_end89(i)

cases = int(input())

for case in range(1,cases+1):
    N = int(input())
    assert N <= limit
    z, s = N, 0
    while z != 0:
        z, d = divmod(z,10)
        s += d*d
    if end89[s]: print('Case #%d: %d is an Unhappy number.'%(case,N))
    else: print('Case #%d: %d is a Happy number.'%(case,N))
