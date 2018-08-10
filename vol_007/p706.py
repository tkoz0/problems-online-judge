
def append_digit(data,s,d):
    h1 = '-' if d in [2,3,5,6,7,8,9,0] else ' ' # chars for horizontals
    h2 = '-' if d in [2,3,4,5,6,8,9] else ' '
    h3 = '-' if d in [2,3,5,6,8,9,0] else ' '
    vl1 = '|' if d in [4,5,6,8,9,0] else ' ' # chars for verticals
    vl2 = '|' if d in [2,6,8,0] else ' '
    vr1 = '|' if d in [1,2,3,4,7,8,9,0] else ' '
    vr2 = '|' if d in [1,3,4,5,6,7,8,9,0] else ' '
    data[0] += ' ' + (h1*s) + ' ' # insert lines with the horizontals
    data[s+1] += ' ' + (h2*s) + ' '
    data[2*s+2] += ' ' + (h3*s) + ' '
    for r in range(1,s+1): data[r] += vl1 + (' '*s) + vr1 # top verticals
    for r in range(s+2,2*s+2): data[r] += vl2 + (' '*s) + vr2 # bottom verticals

while True:
    s, n = map(int,input().split())
    if s == n == 0: break
    assert 1 <= s <= 10
    assert 0 <= n <= 99999999
    n = str(n)
    data = ['']*(2*s+3)
    append_digit(data,s,int(n[0]))
    for d in n[1:]:
        d = int(d)
        for z in range(2*s+3): data[z] += ' ' # space
        append_digit(data,s,d)
    for z in data: print(z)
    print()
