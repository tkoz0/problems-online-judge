
while True:
    try: n = int(input())
    except EOFError: break
    if n == 0: break
    assert n <= 100
    graph = [[] for z in range(n)]
    while True:
        nums = list(map(int,input().split()))
        if nums == [0]: break
        assert nums[-1] == 0
        graph[nums[0]-1] = [z-1 for z in nums[1:-1]] # convert to 0 indexing
    verts = list(map(int,input().split()))
    assert len(verts) == 1+verts[0]
    verts = [z-1 for z in verts[1:]] # convert to 0 indexing
    # use a dfs search (marking visited) to find reachable
    for source in verts:
        visited = [False]*n
        # a vertex is not visitable from itself unless theres a path to it
        # so start from the adjacent vertices and DFS search
        stack = graph[source][:]
        while len(stack): # iteratively implemented DFS
            vertex = stack.pop()
            if not visited[vertex]:
                visited[vertex] = True
                stack += graph[vertex]
        unreachable = []
        # find unreachable (those which were not visited)
        for i,v in enumerate(visited):
            if not v: unreachable.append(i+1) # convert back to 1 indexing
        print(len(unreachable),' '.join(map(str,unreachable)))

