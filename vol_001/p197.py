import sys

# split string into equal length parts
def split(s,n): return [s[i:i+n] for n in range(0,len(s),n)]

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
    cube2 = [[[cube[z][x][y] for z in range(X)] for y in range(Z)]
             for x in range(Y)]
    cube3 = [[[cube[y][z][x] for z in range(Y)] for y in range(X)]
             for x in range(Z)]
    # make the 3 other faces (touching (X-1,Y-1,Z-1)) to be the "top" face
    cube4 = []
    cube5 = []
    cube6 = []
    rot += all_rots(cube2)
    rot += all_rots(cube3)
    rot += all_rots(cube4)
    rot += all_rots(cube5)
    return rot

a = set(compute_rotations(a0))
b = set(compute_rotations(b0))
c = set(compute_rotations(c0))
d = set(compute_rotations(d0))
e = set(compute_rotations(e0))
f = set(compute_rotations(f0))
g = set(compute_rotations(g0))

cube = None
solutions = None

def find_solutions(block): # recursively pick places for a block
    global cube, solutions
    # TODO place block where possible
    if block == 'g': # last block, cube completed
        solutions.append(encode(cube))
    else: find_solutions(chr(ord(block)+1)) # recurse with next letter
    # TODO backtrack

def find_solutions_a(): # translate the position of the 'a' block
    pass
    find_solutions('b') # recurse on variable position block

for line in sys.stdin:
    assert set(line[:-1]) == set('a.')
    cube = decode(line[:-1])
    solutions = []
    find_solutions_a()
    print('\n'.join(sorted(solutions)))
    print()
