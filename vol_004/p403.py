import sys

W, H = 60, 60

# C1 uses A-Z and ' ', space doesnt overwrite data in grid
# C1 stated to allow any printable character

c5bm = { # only '*' mark where to overwrite data in grid
    'A': ['.***..',
          '*...*.',
          '*****.',
          '*...*.',
          '*...*.'],
    
    'B': ['****..',
          '*...*.',
          '****..',
          '*...*.',
          '****..'],
    
    'C': ['.****.',
          '*...*.',
          '*.....',
          '*.....',
          '.****.'],
    
    'D': ['****..',
          '*...*.',
          '*...*.',
          '*...*.',
          '****..'],
    
    'E': ['*****.',
          '*.....',
          '***...',
          '*.....',
          '*****.'],
    
    'F': ['*****.',
          '*.....',
          '***...',
          '*.....',
          '*.....'],
    
    'G': ['.****.',
          '*.....',
          '*..**.',
          '*...*.',
          '.***..'],
    
    'H': ['*...*.',
          '*...*.',
          '*****.',
          '*...*.',
          '*...*.'],
    
    'I': ['*****.',
          '..*...',
          '..*...',
          '..*...',
          '*****.'],
    
    'J': ['..***.',
          '...*..',
          '...*..',
          '*..*..',
          '.**...'],
    
    'K': ['*...*.',
          '*..*..',
          '***...',
          '*..*..',
          '*...*.'],
    
    'L': ['*.....',
          '*.....',
          '*.....',
          '*.....',
          '*****.'],
    
    'M': ['*...*.',
          '**.**.',
          '*.*.*.',
          '*...*.',
          '*...*.'],
    
    'N': ['*...*.',
          '**..*.',
          '*.*.*.',
          '*..**.',
          '*...*.'],
    
    'O': ['.***..',
          '*...*.',
          '*...*.',
          '*...*.',
          '.***..'],
    
    'P': ['****..',
          '*...*.',
          '****..',
          '*.....',
          '*.....'],
    
    'Q': ['.***..',
          '*...*.',
          '*...*.',
          '*..**.',
          '.****.'],
    
    'R': ['****..',
          '*...*.',
          '****..',
          '*..*..',
          '*...*.'],
    
    'S': ['.****.',
          '*.....',
          '.***..',
          '....*.',
          '****..'],
    
    'T': ['*****.',
          '*.*.*.',
          '..*...',
          '..*...',
          '.***..'],
    
    'U': ['*...*.',
          '*...*.',
          '*...*.',
          '*...*.',
          '.***..'],
    
    'V': ['*...*.',
          '*...*.',
          '.*.*..',
          '.*.*..',
          '..*...'],
    
    'W': ['*...*.',
          '*...*.',
          '*.*.*.',
          '**.**.',
          '*...*.'],
    
    'X': ['*...*.',
          '.*.*..',
          '..*...',
          '.*.*..',
          '*...*.'],
    
    'Y': ['*...*.',
          '.*.*..',
          '..*...',
          '..*...',
          '..*...'],
    
    'Z': ['*****.',
          '...*..',
          '..*...',
          '.*....',
          '*****.'],
    
    ' ': ['......',
          '......',
          '......',
          '......',
          '......']
}

grid = list(['.']*W for z in range(H))

def flush():
    global grid
    for r in range(len(grid)):
        print(''.join(grid[r]))
        for c in range(len(grid[r])): grid[r][c] = '.'
    print()
    print('-'*W)
    print()

def getstr(line): # get string that is between the | characters in args
    i1 = line.find('|')
    i2 = line[i1+1:].find('|')
    return line[i1+1:i1+1+i2]

# eight functions for 4 commands with either of the 2 fonts

def pc1(r,c,s): # place s at r,c (top left)
    global grid,W,H
    for cc in range(c,min(W,c+len(s))):
        if s[cc-c] != ' ': grid[r][cc] = s[cc-c]

def pc5(r,c,s): # same as above with c5
    global grid,W,H
    for rr in range(r,min(H,r+5)):
        for cc in range(c,min(W,c+6*len(s))):
            if c5bm[s[(cc-c)//6]][rr-r][(cc-c)%6] == '*': grid[rr][cc] = '*'

def lc1(r,s): pc1(r,0,s)

def lc5(r,s): pc5(r,0,s)

def rc1(r,s):
    global grid,W,H
    s = s[::-1]
    for cc in range(W-1,max(-1,W-1-len(s)),-1):
        ch = s[W-1-cc]
        if ch != ' ': grid[r][cc] = ch

def rc5(r,s):
    global grid,W,H
    for rr in range(r,min(H,r+5)):
        for cc in range(W-1,max(-1,W-1-6*len(s)),-1):
            sc = 6*len(s)-W+cc # column of c5 font grid
            if c5bm[s[sc//6]][rr-r][sc%6] == '*': grid[rr][cc] = '*'

def cc1(r,s):
    global grid,W,H
    gc, sc = W//2, len(s)//2 # corresponding center indexes
    gl, sl = gc-min(W//2,len(s)//2), sc-min(W//2,len(s)//2) # left indexes
    gr, sr = gc+min(W-gc,len(s)-sc), sc+min(W-gc,len(s)-sc) # 1 past right
    for cc in range(gr-gl):
        if s[sl+cc] != ' ': grid[r][gl+cc] = s[sl+cc]

def cc5(r,s):
    global grid,W,H
    gc, sc = W//2, 6*len(s)//2 # corresponding center indexes
    gl, sl = gc-min(W//2,6*len(s)//2), sc-min(W//2,6*len(s)//2) # left indexes
    gr, sr = gc+min(W-gc,6*len(s)-sc), sc+min(W-gc,6*len(s)-sc) # 1 past right
    for rr in range(r,min(H,r+5)):
        for cc in range(gr-gl):
            if c5bm[s[(sl+cc)//6]][rr-r][(sl+cc)%6] == '*':
                grid[rr][gl+cc] = '*'

for line in sys.stdin:
    cmd = list(line.split())
    if cmd[0] == '.P':
        f,r,c,s = cmd[1] == 'C1', int(cmd[2])-1, int(cmd[3])-1, getstr(line)
        if f: pc1(r,c,s)
        else: pc5(r,c,s)
    elif cmd[0] == '.L':
        f, r, s = cmd[1] == 'C1', int(cmd[2])-1, getstr(line)
        if f: lc1(r,s)
        else: lc5(r,s)
    elif cmd[0] == '.R':
        f, r, s = cmd[1] == 'C1', int(cmd[2])-1, getstr(line)
        if f: rc1(r,s)
        else: rc5(r,s)
    elif cmd[0] == '.C':
        f, r, s = cmd[1] == 'C1', int(cmd[2])-1, getstr(line)
        if f: cc1(r,s)
        else: cc5(r,s)
    else:
        assert cmd[0] == '.EOP'
        flush()
