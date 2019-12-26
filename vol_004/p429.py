
N = int(input())
input()

def dif1letter(a,b): # if words are same length and differ at 1 position
    if len(a) != len(b): return False
    count = 0
    for i in range(len(a)):
        if a[i] == b[i]: continue
        count += 1
        if count > 1: break
    return count == 1

for _ in range(N):
    if _ != 0: print()
    dic = []
    while True:
        w = input()
        if w == '*': break
        dic.append(w)
    assert len(dic) <= 200
    word2node = dict() # mapping
    for i,w in enumerate(dic): word2node[w] = i
    graph = [[] for __ in range(len(dic))] # use numbers to label nodes
    for i in range(len(dic)): # make edges in graph
        for j in range(i+1,len(dic)):
            if dif1letter(dic[i],dic[j]):
                graph[i].append(j)
                graph[j].append(i)
    while True: # for each word pair to test
        try: a,b = input().split()
        except Exception: break # eof or blank line ends test case
        # use BFS to find shortest path from a to b, nodes u and v respectively
        u = word2node[a]
        v = word2node[b]
        visited = [False]*len(dic)
        Q = [u]
        dist = 0
        while Q != []:
            Q2 = [] # next layer
            for x in Q:
                if visited[x]: continue
                visited[x] = True
                Q2 += [y for y in graph[x] if not visited[y]]
            dist += 1
            if v in Q2: break
            Q = Q2
        assert Q != [] # guaranteed path to exist by specification
        print(a,b,dist)
