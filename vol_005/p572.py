
while True:
    m, n = map(int,input().split())
    if m == 0: break
    assert 1 <= m <= 100
    assert 1 <= n <= 100
    grid = list(list(input()) for z in range(m))
    # compute number of components in a "grid graph" with 8 directions
    # when finding an oil deposit, "take all the oil" and replace its @ with *
    components = 0
    for r in range(m):
        for c in range(n):
            if grid[r][c] != '@': continue
            components += 1 # found oil, collect deposit (1 graph component)
            stack = [(r,c)]
            while len(stack) != 0:
                p = stack.pop() # out of bounds check
                if p[0] < 0 or p[0] >= m or p[1] < 0 or p[1] >= n: continue
                if grid[p[0]][p[1]] == '@':
                    grid[p[0]][p[1]] = '*' # collect partial oil deposit
                    stack.append((p[0]+1,p[1]+1)) # search surrounding
                    stack.append((p[0]+1,p[1]-1))
                    stack.append((p[0]+1,p[1]))
                    stack.append((p[0]-1,p[1]+1))
                    stack.append((p[0]-1,p[1]-1))
                    stack.append((p[0]-1,p[1]))
                    stack.append((p[0],p[1]+1))
                    stack.append((p[0],p[1]-1))
    print(components)
