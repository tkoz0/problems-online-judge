
cases = int(input())

for _ in range(cases):
    maze = []
    end_line = ''
    while True:
        line = input()
        if set(line) == set('_'):
            end_line = line
            break
        maze.append(list(line))
    wall = ''
    for r,row in enumerate(maze):
        found = False
        for c,col in enumerate(maze[r]):
            if col != ' ' and col != '*' and col != '_':
                wall = col
                found = True
                break
        if found: break
    assert wall != ''
    # find wall char
    # find * (start position)
    sr, sc = -1, -1
    for r,row in enumerate(maze):
        found = False
        for c,col in enumerate(maze[r]):
            if col == '*':
                sr, sc = r, c
                found = True
                break
        if found: break
    assert sr != -1 and sc != -1
    # iterative DFS to paint explorable area
    stack = [(sr,sc)]
    while len(stack):
        r, c = stack.pop() # get position, check bounds
        if r < 0 or r >= len(maze) or c < 0 or c >= len(maze[r]): continue
        if maze[r][c] == '#' or maze[r][c] == wall: continue # not explorable
        maze[r][c] = '#'
        stack += [(r+1,c),(r,c+1),(r-1,c),(r,c-1)] # DFS
    for r in maze: print(''.join(r))
    print(end_line)

