
upper = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
cases = int(input())
assert input() == ''

for z in range(cases):
    nodes = 1+upper.find(input())
    assert nodes != 0
    adj = dict()
    for c in upper[:nodes]: adj[c] = set()
    while True:
        try: e = input()
        except EOFError: break # EOF, should be at end of last case
        if e == '': break # blank line separator
        assert e[0] != e[1]
        adj[e[0]].add(e[1])
        adj[e[1]].add(e[0])
    components = 0
    visited = set()
    for v in upper[:nodes]:
        if v in visited: continue
        components += 1 # new component, visit every other vertex in it
        stack = [v]
        while len(stack) != 0:
            u = stack.pop()
            if u in visited: continue
            visited.add(u)
            for uu in adj[u]: stack.append(uu)
    if z != 0: print() # blank line between cases
    print(components)
