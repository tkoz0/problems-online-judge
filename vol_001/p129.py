alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

def print_seq(s):
    for i in range(0,len(s),64):
        print(s[i:min(i+4,len(s))],end='')
        for j in range(i+4,min(i+64,len(s)),4):
            print(' %s'%s[j:j+4],end='')
        print()
    print(len(s))

def ends_with_rep(s):
    l = len(s)
    for i in range(1,1+len(s)//2): # num ending chars to compare
        if s[l-i:l] == s[l-2*i:l-i]:
            return True
    return False

def gen_seq(L):
    seq = ''
    possible = [list(alpha[:L])] # which letters could go in position
    while len(possible) > 0:
        if len(seq) < len(possible):
            seq += possible[-1].pop(0)
            yield seq
#            print('y',seq,possible)
        else: # new recursion depth
            possible.append([])
            for c in alpha[:L]:
                if not ends_with_rep(seq+c):
                    possible[-1].append(c)
#            print('s',seq,possible)
            while len(possible) > 0 and len(possible[-1]) == 0: # backtrack
                possible.pop()
                seq = seq[:-1]

while True:
    n, L = map(int,input().split())
    if n == 0 and L == 0: break
    seqs = gen_seq(L)
    for i,s in enumerate(seqs):
#        print(':',s)
        if i == n-1:
            print_seq(s)
            break
