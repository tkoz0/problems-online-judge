
MAX = 100

def roman(i):
    assert i <= 100
    if i == 100: return 'c'
    t, o = i//10, i%10
    return ['','x','xx','xxx','xl','l','lx','lxx','lxxx','xc'][t] + \
            ['','i','ii','iii','iv','v','vi','vii','viii','ix'][o]

strs = list(roman(i) for i in range(MAX+1))
cumul = dict()
for char in ['i','v','x','l','c']:
    cumul[char] = [0]
    for i in range(1,MAX+1):
        cumul[char].append(cumul[char][-1]+strs[i].count(char))

while True:
    N = int(input())
    if N == 0: break
    assert N <= MAX
    print('%d: %d i, %d v, %d x, %d l, %d c'%(N,
        cumul['i'][N],cumul['v'][N],cumul['x'][N],cumul['l'][N],cumul['c'][N]))
