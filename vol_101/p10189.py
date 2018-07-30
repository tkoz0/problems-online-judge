
def populate(field):
    deltas = [(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1),(0,-1),(1,-1)]
    for r in range(len(field)):
        for c in range(len(field[0])):
            if field[r][c] == '*': continue
            count = 0
            for d in deltas:
                rr, cc = r+d[0], c+d[1]
                if 0 <= rr < len(field) and 0 <= cc < len(field[0]) \
                    and field[rr][cc] == '*': count += 1
            field[r][c] = str(count)

fnum = 0
while True:
    fnum += 1
    n, m = map(int,input().split())
    if n == 0 and m == 0: break
    if fnum != 1: print() # empty line to separate from previous case
    field = []
    for z in range(n): field.append(list(input()))
    populate(field)
    print('Field #%d:'%fnum)
    for z in field: print(''.join(z))
