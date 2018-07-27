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
    odd = input() == 'O' # parity type
    disks = []
    for z in range(d): # read disk data, split by blocks
        istr = input()
        assert len(istr) == s*b
        disks.append(list(list(istr[i:i+s]) for i in range(0,len(istr),s)))
    valid = True
    for block in range(b): # solve for unknowns
        if not valid: break
        for bit in range(s):
            xcount, xi = 0, -1 # count unknowns and index of an unknown (disk #)
            for z in range(d):
                if disks[z][block][bit] == 'x': xcount += 1; xi = z
            if xcount > 1: valid = False; break
            if xcount == 1: # must recalculate unavaliable bit
                u = 1 if odd else 0 # compute unavailable value
                for z in range(d):
                    if z != xi: u ^= int(disks[z][block][bit])
                disks[xi][block][bit] = str(u)
            p = 0 # verify that xor of disks = parity type
            for z in range(d): p ^= int(disks[z][block][bit])
            if p != (1 if odd else 0): valid = False; break
    hexstr = '' # concatenate non parity blocks
    if valid:
        for block in range(b):
            for disk in range(d):
                if disk != block % d: hexstr += ''.join(disks[disk][block])
    while len(hexstr) % 4 != 0: hexstr += '0'
    if hexstr != '': hexstr = '%X' % int(hexstr,2) # convert to hexadecimal
    if valid: print('Disk set %d is valid, contents are: %s' % (counter,hexstr))
    else: print('Disk set %d is invalid.' % counter)
