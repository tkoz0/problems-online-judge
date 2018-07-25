import sys

cases = int(input())

for case in range(cases):
    x, y = map(int,input().split()) # start
    sx, sy = x, y
    path = input()
    bitmap = [] # initially 32x32 grid of ., indexed as [y][x]
    for z in range(32): bitmap.append(['.']*32)
    for s in path: # follow path (counterclockwise)
        assert x > 0 and x < 32 and y > 0 and y < 32 # never reaches boundaries
        if s == 'E': bitmap[y-1][x] = 'X'; x += 1
        elif s == 'N': bitmap[y][x] = 'X'; y += 1
        elif s == 'W': bitmap[y][x-1] = 'X'; x -= 1
        elif s == 'S': bitmap[y-1][x-1] = 'X'; y -= 1
        else: assert s == '.' # end of path
    assert x == sx and y == sy # path was closed
    print('Bitmap #%d' % (case+1))
    for row in bitmap[::-1]: print(''.join(row))
    print()
