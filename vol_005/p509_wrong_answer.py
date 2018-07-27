import sys

counter = 0
for line in sys.stdin:
    counter += 1
    params = line.split()
    if int(params[0]) == 0: break # last "disk set"
    d, s, b = int(params[0]), int(params[1]), int(params[2])
    assert 2 <= d <= 6
    assert 1 <= s <= 64
    assert 1 <= b <= 100
    parity = (1 if input() == 'O' else 0) # parity type
    disks = []
    for z in range(d): # read disk data
        disks.append(list(input()))
        assert len(disks[-1]) == s*b
    valid = True
    for bit in range(s*b):
        xs, xi = 0, -1 # unknowns and disk# for an unknown bit
        for disk in range(d):
            if disks[disk][bit] == 'x': xs += 1; xi = disk
        if xs > 1: valid = False; break # cannot recover data
        if xs == 1: # recover missing bit
            u = parity
            for disk in range(d):
                if disk != xi: u ^= int(disks[disk][bit])
            disks[xi][bit] = str(u)
        p = 0
        for disk in range(d): p ^= int(disks[disk][bit])
        if p != parity: valid = False; break
    data = '' # make binary string of data by concatenating non parity blocks
    if valid:
        for block in range(b):
            for disk in range(d):
                if disk != block % d: data += \
                                        ''.join(disks[disk][s*block:s*block+s])
    while len(data) % 4 != 0: data += '0'
    if data != '': data = '%X' % int(data,2)
    if valid: print('Disk set %d is valid, contents are: %s' % (counter,data))
    else: print('Disk set %d is invalid.' % counter)
