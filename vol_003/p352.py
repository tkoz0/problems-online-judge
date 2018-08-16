
case = 0
while True:
    case += 1
    try: s = int(input())
    except EOFError: break
    assert s <= 25
    img = list(list(input()) for z in range(s))
    # number of components of the grid graph (ignoring 0)
    marked = list([False]*s for z in range(s))
    eagles = 0
    for r in range(s):
        for c in range(s):
            if img[r][c] == '1' and not marked[r][c]: # new component of 1s
                eagles += 1
                # mark entire component
                stack = [(r,c)]
                while len(stack) != 0:
                    u = stack.pop()
                    if not (0 <= u[0] < s) or not (0 <= u[1] < s): continue
                    if img[u[0]][u[1]] != '1' or marked[u[0]][u[1]]: continue
                    # unmarked 1, mark this and push adjacent
                    marked[u[0]][u[1]] = True
                    for d in [(1,-1),(1,0),(1,1),(0,1),
                              (0,-1),(-1,-1),(-1,1),(-1,0)]:
                        stack.append((u[0]+d[0],u[1]+d[1]))
    print('Image number %d contains %d war eagles.'%(case,eagles))
