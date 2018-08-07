import sys

r1 = '`1234567890-='
r2 = 'qwertyuiop[]\\'
r3 = 'asdfghjkl;\''
r4 = 'zxcvbnm,./'
r1u = '~!@#$%^&*()_+' # while shift key is pressed
r2u = 'QWERTYUIOP{}|'
r3u = 'ASDFGHJKL:"'
r4u = 'ZXCVBNM<>?'

def decode(line):
    global r1, r2, r3, r4
    ret = ''
    for c in line:
        i = r1.find(c)
        if i != -1: ret += r1[i-2]; continue
        i = r2.find(c)
        if i != -1: ret += r2[i-2]; continue
        i = r3.find(c)
        if i != -1: ret += r3[i-2]; continue
        i = r4.find(c)
        if i != -1: ret += r4[i-2]; continue
        i = r1u.find(c)
        if i != -1: ret += r1u[i-2]; continue
        i = r2u.find(c)
        if i != -1: ret += r2u[i-2]; continue
        i = r3u.find(c)
        if i != -1: ret += r3u[i-2]; continue
        i = r4u.find(c)
        if i != -1: ret += r4u[i-2]; continue
        ret += c # not a char on qwerty keyboard, leave as is
    return ret

while True:
    try: line = input()
    except EOFError: break
    print(decode(line).lower())
