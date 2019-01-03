
while True:
    n = int(input())
    if n == 0: break # last test case ended
    m = int(input())
    assert 2 <= n <= 100
    # street weights are 1 to 1000
    # nodes given in 1..n ordering, convert to 0..n-1
    graph = [dict() for _ in range(n)] # node --> (adj node --> weight)
    for _ in range(m):
        u, v, w = map(int,input().split()) # edge uv, weight w
        graph[u-1][v-1] = w # make bidirectional edge (undirected graph)
        graph[v-1][u-1] = w
    pass # todo find shortest cycle containing nodes 0 and n-1
    # if cycle exists from 0 to n-1, there are 2 disjoint paths between them
    # find shortest path, remove, find next shortest doesnt work
    # for a counterexample, construct the input file:
    # 5
    # 6
    # 1 2 10
    # 1 3 15
    # 2 4 3
    # 3 4 15
    # 2 5 10
    # 4 5 5
    # one possible algorithm might be to try all paths between 0 and n-1, then
    # find the shortest path after removing it to complete a cycle
    # problem is all paths between 0 and n-1 could be very large

