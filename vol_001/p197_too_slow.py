import sys
from functools import reduce

# split string into equal length parts
def split(s,n): return [s[i:i+n] for i in range(0,len(s),n)]

def decode(s): # 27 char string to cube (3x3x3 array)
    assert len(s) == 27
    return [[list(row) for row in split(flat,3)] for flat in split(s,9)]

def encode(cube): # cube to 27 char string
    s = ''.join(''.join(''.join(row) for row in flat) for flat in cube)
    assert len(s) == 27
    return s

# orientations of the 7 pieces as given
a0 = [[['a','a','a']],[['.','.','a']]]
b0 = [[['b','b'],['b','.']]]
c0 = [[['.','c','.']],[['c','c','c']]]
d0 = [[['d','.'],['d','d'],['.','d']]]
e0 = [[['e','e'],['.','e']],[['.','e'],['.','.']]]
f0 = [[['.','.'],['.','f']],[['f','f'],['.','f']]]
g0 = [[['.','.'],['g','g']],[['.','g'],['.','g']]]

def rot0(flat):
    return [row[:] for row in flat]
def rot90(flat):
    return [ [ flat[c][len(flat[0])-1-r]
               for c in range(len(flat))]
             for r in range(len(flat[0]))]
def rot180(flat):
    return [r[::-1] for r in flat[::-1]]
def rot270(flat):
    return [ [ flat[len(flat)-1-c][r]
               for c in range(len(flat))]
             for r in range(len(flat[0]))]

def all_rots(cube):
    return [[rot0(f) for f in cube],
            [rot90(f) for f in cube],
            [rot180(f) for f in cube],
            [rot270(f) for f in cube]]

def compute_rotations(cube): # computes all 24 rotations of an array
    X, Y, Z = len(cube), len(cube[0]), len(cube[0][0])
    rot = all_rots(cube)
    # make the other faces touching (0,0,0) to be the "top" face
    # cube1: cube[x][y][z] for z(Z) for y(Y) for x(X)
    cube2 = [[[cube[z][x][y] for z in range(X)] for y in range(Z)]
             for x in range(Y)]
    cube3 = [[[cube[y][z][x] for z in range(Y)] for y in range(X)]
             for x in range(Z)]
    # make the 3 other faces (touching (X-1,Y-1,Z-1)) to be the "top" face
    cube4 = [[[cube[X-1-z][Y-1-y][Z-1-x] for z in range(X)] for y in range(Y)]
             for x in range(Z)]
    cube5 = [[[cube[X-1-y][Y-1-x][Z-1-z] for z in range(Z)] for y in range(X)]
             for x in range(Y)]
    cube6 = [[[cube[X-1-x][Y-1-z][Z-1-y] for z in range(Y)] for y in range(Z)]
             for x in range(X)]
    rot += all_rots(cube2)
    rot += all_rots(cube3)
    rot += all_rots(cube4)
    rot += all_rots(cube5)
    rot += all_rots(cube6)
    return rot

def dedup(l): # since lists arent hashable, just use a O(n^2) loop
    l2 = []
    for e in l:
        if not (e in l2): l2.append(e)
    return l2

def flatX0(cube): return cube[0]
def flatX1(cube): return cube[len(cube)-1]
def flatY0(cube): return [[cube[x][0][z] for z in range(len(cube[0][0]))]
                          for x in range(len(cube))]
def flatY1(cube): return [[cube[x][len(cube[0])-1][z]
                           for z in range(len(cube[0][0]))]
                          for x in range(len(cube))]
def flatZ0(cube): return [[cube[x][y][0] for y in range(len(cube[0]))]
                          for x in range(len(cube))]
def flatZ1(cube): return [[cube[x][y][len(cube[0][0])-1]
                           for y in range(len(cube[0]))]
                          for x in range(len(cube))]
def flatEmpty(flat): return reduce(lambda x,y:x|y,[set(r) for r in flat]) \
                            == set('.')
def truncate(cube): # remove empty faces, assumes cube is nonempty
    while flatEmpty(flatX0(cube)): cube = cube[1:]
    while flatEmpty(flatX1(cube)): cube = cube[:-1]
    while flatEmpty(flatY0(cube)):
        cube = [[[cube[x][y][z] for z in range(len(cube[0][0]))]
                  for y in range(1,len(cube[0]))] for x in range(len(cube))]
    while flatEmpty(flatY1(cube)):
        cube = [[[cube[x][y][z] for z in range(len(cube[0][0]))]
                  for y in range(len(cube[0])-1)] for x in range(len(cube))]
    while flatEmpty(flatZ0(cube)):
        cube = [[cube[x][y][1:] for y in range(len(cube[0]))]
                for x in range(len(cube))]
    while flatEmpty(flatZ1(cube)):
        cube = [[cube[x][y][:-1] for y in range(len(cube[0]))]
                for x in range(len(cube))]
    return cube

# all possible unique rotations for each piece
a = dedup(compute_rotations(a0))
b = dedup(compute_rotations(b0))
c = dedup(compute_rotations(c0))
d = dedup(compute_rotations(d0))
e = dedup(compute_rotations(e0))
f = dedup(compute_rotations(f0))
g = dedup(compute_rotations(g0))

cube = None
solutions = None

def place_block(x0,y0,z0,block): # adds block to position, return successful
    global cube
    X, Y, Z = len(block), len(block[0]), len(block[0][0])
    if x0 + X > 3 or y0 + Y > 3 or z0 + Z > 3: return False # out of bounds
    for x in range(X):
        for y in range(Y):
            for z in range(Z):
                if block[x][y][z] != '.' and cube[x0+x][y0+y][z0+z] != '.':
                    return False # cannot overwrite occupied space
    for x in range(X):
        for y in range(Y):
            for z in range(Z):
                if block[x][y][z] != '.':
                    cube[x0+x][y0+y][z0+z] = block[x][y][z]
    return True

def remove_block(x0,y0,z0,block): # removes block, assumes it was validly placed
    global cube
    X, Y, Z = len(block), len(block[0]), len(block[0][0])
    for x in range(X):
        for y in range(Y):
            for z in range(Z):
                if block[x][y][z] != '.': cube[x0+x][y0+y][z0+z] = '.'

def find_solutions(block_code): # recursively pick places for a block
    global cube, solutions
    if block_code == 'h': # placed all blocks, cube complete
        solutions.append(encode(cube))
    else:
        # place block, first pick which possibilities for this block code
        possible = {'b':b,'c':c,'d':d,'e':e,'f':f,'g':g}[block_code]
        for block in possible: # try each orientation
            X, Y, Z = len(block), len(block[0]), len(block[0][0])
            for x0 in range(3+1-X):
                for y0 in range(3+1-Y):
                    for z0 in range(3+1-Z):
                        if place_block(x0,y0,z0,block):
                            find_solutions(chr(ord(block_code)+1)) # next letter
                            remove_block(x0,y0,z0,block) # backtrack

def find_solutions_a(): # translate the position of the 'a' block
    global cube, solutions
    a_part = truncate(cube)
    assert a_part in a
    X, Y, Z = len(a_part), len(a_part[0]), len(a_part[0][0])
    for x0 in range(3+1-X): # pick from possible initial start positions
        for y0 in range(3+1-Y):
            for z0 in range(3+1-Z): # make blank cube and place "a" piece
                cube = [[['.']*3,['.']*3,['.']*3],[['.']*3,['.']*3,['.']*3],
                        [['.']*3,['.']*3,['.']*3]]
                success = place_block(x0,y0,z0,a_part)
                assert success # should succeed since cube is empty
                print('placed a at (%d,%d,%d)'%(x0,y0,z0))
                find_solutions('b') # recurse on variable position block

#print('rotation counts',len(a),len(b),len(c),len(d),len(e),len(f),len(g))

for line in sys.stdin:
    assert set(line[:-1]) == set('a.')
    cube = decode(line[:-1])
    solutions = []
    find_solutions_a()
    print('\n'.join(sorted(solutions)))
    print(len(solutions))
