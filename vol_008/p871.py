
cases = int(input())
assert input() == '' # skip blank line

for _ in range(cases):
    grid = []
    while True:
        try: line = input()
        except EOFError: break
        if line == '': break
        grid.append(line)
    assert len(grid) > 0
    for __ in grid: assert len(__) == len(grid[0])
    visited = [[False]*len(grid[0]) for __ in range(len(grid))]
    largest = 0
    for r in range(len(grid)):
        for c in range(len(grid[0])):
            if visited[r][c] or grid[r][c] == '0': continue
            size = 0
            stack = [(r,c)]
            while len(stack) != 0:
                rr,cc = stack.pop()
                if rr < 0 or rr >= len(grid) or cc < 0 or cc >= len(grid[0]):
                    continue
                # part of blob
                if grid[rr][cc] == '1' and (not visited[rr][cc]):
                    visited[rr][cc] = True
                    size += 1
                    for i in [-1,0,1]: # recurse on surrounding
                        for j in [-1,0,1]:
                            stack.append((rr+i,cc+j))
            largest = max(largest,size)
    if _: print()
    print(largest)

