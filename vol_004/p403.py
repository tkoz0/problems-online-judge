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
    i = line.find('|')
    return line[i+1:line[i+1:].find('|')]

# eight functions for 4 commands with either of the 2 fonts

def pc1(r,c,s):
    global grid

def pc5(r,c,s):
    global grid

def lc1(r,s):
    global grid

def lc5(r,s):
    global grid

def rc1(r,s):
    global grid

def rc5(r,s):
    global grid

def cc1(r,s):
    global grid

def cc5(r,s):
    global grid

for line in sys.stdin:
    cmd = list(line.split())
    if cmd[0] == '.P':
        f,r,c,s = line[1] == 'C1', int(line[2])-1, int(line[3])-1, getstr(line)
        if f: pc1(r,c,s)
        else: pc5(r,c,s)
    elif cmd[0] == '.L':
        f, r, s = line[1] == 'C1', int(line[2])-1, getstr(line)
        if f: lc1(r,s)
        else: lc5(r,s)
    elif cmd[0] == '.R':
        f, r, s = line[1] == 'C1', int(line[2])-1, getstr(line)
        if f: rc1(r,s)
        else: rc5(r,s)
    elif cmd[0] == '.C':
        f, r, s = line[1] == 'C1', int(line[2])-1, getstr(line)
        if f: cc1(r,s)
        else: cc5(r,s)
    else:
        assert cmd[0] == '.EOP'
        flush()
