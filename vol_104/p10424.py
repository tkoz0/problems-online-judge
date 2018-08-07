
def digital_root(n): # from wikipedia
    if n == 0: return 0
    if n % 9 == 0: return 9
    return n % 9

chars = ' abcdefghijklmnopqrstuvwxyz'

while True:
    try:
        s1 = input()
        s2 = input()
    except EOFError: break
    s1 = s1.lower()
    s2 = s2.lower()
    s1val, s2val = 0, 0
    for c in s1:
        val = chars.find(c)
        if val != -1: s1val += val
    for c in s2:
        val = chars.find(c)
        if val != -1: s2val += val
    s1dr, s2dr = digital_root(s1val), digital_root(s2val)
    if s1dr < s2dr: print('%.2f %%' % (100.0*s1dr/s2dr))
    else: print('%.2f %%' % (100.0*s2dr/s1dr))
