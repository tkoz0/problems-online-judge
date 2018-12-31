
while True:
    try: n = int(input())
    except EOFError: break
    if n == 0: break
    graph = [[] for z in range(n)]
    while True:
        nums = list(map(int,input().split()))
        if nums == [0]: break
        graph[nums[0]-1] = [z-1 for z in nums[1:-1]] # convert to 0 indexing
    verts = list(map(int,input().split()))
    assert len(verts) == 1+verts[0]
    verts = verts[1:]

# use a dfs search (marking visited) to find reachable
# then unreachable is set of all set minus the reachable set
