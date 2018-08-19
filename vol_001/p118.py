
X1, Y1 = 0, 0 # lower left
X2, Y2 = map(int,input().split()) # upper right
assert X2 >= 0
assert Y2 >= 0
scent = set() # set of coordinates where robot previously fell
move_vector = {'N':(0,1),'S':(0,-1),'E':(1,0),'W':(-1,0)} # directions to unit
rot_L = {'N':'W','S':'E','E':'N','W':'S'} # left rotate
rot_R = {'N':'E','S':'W','E':'S','W':'N'} # right rotate
while True: # process 1 robot at a time
    try: line = input().split()
    except EOFError: break
    x, y = int(line[0]), int(line[1])
    assert X1 <= x <= X2
    assert Y1 <= y <= Y2
    dir = line[2] # letter indicating direction
    mv = move_vector[dir]
    instructions = input()
    fell = False
    for i in instructions:
        if i == 'L': dir = rot_L[dir]; mv = move_vector[dir]
        elif i == 'R': dir = rot_R[dir]; mv = move_vector[dir]
        elif i == 'F': # step forward
            x, y = x+mv[0], y+mv[1]
            if not (X1 <= x <= X2) or not (Y1 <= y <= Y2):
                x, y = x-mv[0], y-mv[1] # keep last position
                if not ((x,y) in scent): fell = True; scent.add((x,y)); break
    if fell: print(x,y,dir,'LOST')
    else: print(x,y,dir)
