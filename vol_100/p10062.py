
first = True
while True:
    try: line = input()
    except EOFError: break
    freq = dict()
    for c in line:
        i = ord(c)
        if not (i in freq): freq[i] = 0
        freq[i] += 1
    if not first: print()
    out = list((-freq[k],k) for k in freq.keys())
    out = sorted(out,reverse=True)
    for item in out: print(item[1],-item[0])
    first = False
