
def recurse_b2d(bm,rmin,rmax,cmin,cmax):
    uniform = True
    bit = bm[rmin][cmin]
    for r in range(rmin,rmax):
        for c in range(cmin,cmax):
            if bm[r][c] != bit: uniform = False; break
    if uniform: return bit # 1 char representing a uniform color region
    else: # must divide into sub-blocks, concatenate strings for each region
        assert rmax-rmin > 1 or cmax-cmin > 1
        rmid, cmid = rmin + (1+rmax-rmin)//2, cmin + (1+cmax-cmin)//2
        result = 'D'
        if rmax-rmin == 1: # divide row
            result += recurse_b2d(bm,rmin,rmax,cmin,cmid)
            result += recurse_b2d(bm,rmin,rmax,cmid,cmax)
        elif cmax-cmin == 1: # divide column
            result += recurse_b2d(bm,rmin,rmid,cmin,cmax)
            result += recurse_b2d(bm,rmid,rmax,cmin,cmax)
        else: # divide into 4 regions
            result += recurse_b2d(bm,rmin,rmid,cmin,cmid)
            result += recurse_b2d(bm,rmin,rmid,cmid,cmax)
            result += recurse_b2d(bm,rmid,rmax,cmin,cmid)
            result += recurse_b2d(bm,rmid,rmax,cmid,cmax)
        return result

def B2D(data,R,C):
    bm = list(list(data[z:z+C]) for z in range(0,R*C,C))
    return recurse_b2d(bm,0,R,0,C)

def D2B(data,R,C):
    bm = list(['0']*C for z in range(R))
    stack = [(0,R,0,C)]
    for ch in data:
        assert len(stack) > 0
        rmin, rmax, cmin, cmax = stack.pop()
        if ch == '1': # fill region with 1 bits
            for r in range(rmin,rmax):
                for c in range(cmin,cmax): bm[r][c] = '1'
        # if ch=='0' then dont overwrite '0' with '0' for speed
        elif ch == 'D': # push sub-block positions to stack
            # they must be pushed in reverse of order they are processed in data
            assert rmax-rmin > 1 or cmax-cmin > 1 # cannot divide single bit
            rmid, cmid = rmin + (1+rmax-rmin)//2, cmin + (1+cmax-cmin)//2
            if rmax-rmin == 1: # divide row
                stack.append((rmin,rmax,cmid,cmax))
                stack.append((rmin,rmax,cmin,cmid))
            elif cmax-cmin == 1: # divide column
                stack.append((rmid,rmax,cmin,cmax))
                stack.append((rmin,rmid,cmin,cmax))
            else: # divide into 4 regions
                stack.append((rmid,rmax,cmid,cmax))
                stack.append((rmid,rmax,cmin,cmid))
                stack.append((rmin,rmid,cmid,cmax))
                stack.append((rmin,rmid,cmin,cmid))
    assert len(stack) == 0
    return ''.join(''.join(row) for row in bm)

info = input()
while True:
    if info == '#': break
    info = info.split()
    fmt = info[0]
    R = int(info[1])
    C = int(info[2])
    assert R <= 200 and C <= 200
    data = ''
    while True:
        line = input()
        if (' ' in line) or line == '#': info = line; break # for next bitmap
        data += line
    if fmt == 'B':
        print('D%4d%4d'%(R,C))
        out = B2D(data,R,C)
        for s in (out[i:i+50] for i in range(0,len(out),50)): print(s)
    else:
        assert fmt == 'D'
        print('B%4d%4d'%(R,C))
        out = D2B(data,R,C)
        for s in (out[i:i+50] for i in range(0,len(out),50)): print(s)
