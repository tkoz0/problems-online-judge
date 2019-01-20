
N = int(input())
assert N <= 15

for _ in range(N):
    name, R, C = input().split()
    R, C = int(R), int(C)
    assert 1 <= R <= 100
    assert 1 <= C <= 100
    input_grid = [list(map(int,input().split())) for __ in range(R)]
    for __ in input_grid: assert len(__) == C

    incoming = [[0]*C for __ in range(R)] # num incoming edges
    # 4 bool array: from (r,c) to [(r,c+1),(r-1,c),(r,c-1),(r+1,c)]
    outgoing = [[[False]*4 for ___ in range(C)]
                for __ in range(R)] # adjacent vertices

    # build directed acyclic graph information
    for r in range(R):
        for c in range(C):
            if r > 0 and input_grid[r-1][c] < input_grid[r][c]:
                incoming[r-1][c] += 1
                outgoing[r][c][1] = True
            if r < R-1 and input_grid[r+1][c] < input_grid[r][c]:
                incoming[r+1][c] += 1
                outgoing[r][c][3] = True
            if c > 0 and input_grid[r][c-1] < input_grid[r][c]:
                incoming[r][c-1] += 1
                outgoing[r][c][2] = True
            if c < C-1 and input_grid[r][c+1] < input_grid[r][c]:
                incoming[r][c+1] += 1
                outgoing[r][c][0] = True

    top_sort = [] # topological sorting of the directed acyclic graph
    no_incom = [] # vertices with no incoming edges
    for r in range(R):
        for c in range(C):
            if incoming[r][c] == 0: no_incom.append((r,c))
    while len(no_incom) != 0:
        r,c = no_incom.pop() # get vertex
        top_sort.append((r,c))
        if outgoing[r][c][0]: # (r,c+1)
            outgoing[r][c][0] = False # remove from graph
            incoming[r][c+1] -= 1
            if incoming[r][c+1] == 0:
                no_incom.append((r,c+1))
        if outgoing[r][c][1]: # (r-1,c)
            outgoing[r][c][1] = False
            incoming[r-1][c] -= 1
            if incoming[r-1][c] == 0:
                no_incom.append((r-1,c))
        if outgoing[r][c][2]: # (r,c-1)
            outgoing[r][c][2] = False
            incoming[r][c-1] -= 1
            if incoming[r][c-1] == 0:
                no_incom.append((r,c-1))
        if outgoing[r][c][3]: # (r+1,c)
            outgoing[r][c][3] = False
            incoming[r+1][c] -= 1
            if incoming[r+1][c] == 0:
                no_incom.append((r+1,c))

    # sanity check, graph is actually acyclic (no edges left)
    for r in range(R):
        for c in range(C):
            for z in range(3):
                assert not outgoing[r][c][z]
            assert incoming[r][c] == 0
    assert len(top_sort) == R*C

    longest = [[-1]*C for __ in range(R)]
    for i in range(len(top_sort)-1,-1,-1):
        r,c = top_sort[i]
        best_choice = 0 # longest subpath following this vertex
        if r > 0 and input_grid[r-1][c] < input_grid[r][c]:
            best_choice = max(best_choice,longest[r-1][c])
        if r < R-1 and input_grid[r+1][c] < input_grid[r][c]:
            best_choice = max(best_choice,longest[r+1][c])
        if c > 0 and input_grid[r][c-1] < input_grid[r][c]:
            best_choice = max(best_choice,longest[r][c-1])
        if c < C-1 and input_grid[r][c+1] < input_grid[r][c]:
            best_choice = max(best_choice,longest[r][c+1])
        longest[r][c] = 1+best_choice

    print('%s: %d'%(name,max(max(longest[__]) for __ in range(R))))
