
while True:
    code = input()
    if code == '#': break
    code = list(code)
    assert len(code) != 0
    # generate next lexicographic permutation
    i1 = len(code)-1
    while i1 != 0 and code[i1-1] >= code[i1]: i1 -= 1
    i1 -= 1 # breaks noninc order
    if i1 == -1: print('No Successor'); continue
    i2 = len(code)-1 # smallest value that exceeds i1 value
    while code[i2] <= code[i1]: i2 -= 1
    code[i1], code[i2] = code[i2], code[i1]
    i1 += 1
    i2 = len(code)-1
    while i1 < i2:
        code[i1], code[i2] = code[i2], code[i1]
        i1 += 1
        i2 -= 1
    print(''.join(code))
