import sys

def decode(s):
    result = ''
    rep = 0
    for c in s:
        if c in '0123456789': rep += int(c)
        elif c == 'b': result += ' '*rep; rep = 0
        else: result += c*rep; rep = 0
    return result

first = True
for line in sys.stdin:
    if line == '\n': continue
    data = line[:-1]
    while True: # read consecutive lines until blank or EOF
        try:
            line2 = input()
        except EOFError: break
        if line2 == '': break
        data += '!' + line2 # new rows separated by ! or \n
    if not first: print()
    print('\n'.join(decode(row) for row in data.split('!')))
    first = False
