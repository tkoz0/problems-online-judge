
cases = int(input())
assert input() == ''

for case in range(cases):
    comps = int(input())
    # index i is set i, it is a list of computers in a graph component
    disjsets = list([i] for i in range(1,1+comps))
    memberof = [0]+list(range(comps)) # computer i in set memberof[i]
    right, wrong = 0, 0 # for queries
    while True:
        try: line = input()
        except EOFError: break
        if line == '': break
        line = line.split()
        u, v = int(line[1]), int(line[2]) # the 2 computers
        su, sv = memberof[u], memberof[v] # sets they are in
        if line[0] == 'c': # make connection (join graph components / sets)
            if su != sv: # move all in sv to su
                for comp in disjsets[sv]: memberof[comp] = su
                disjsets[su] += disjsets[sv][:]
                disjsets[sv] = [] # clear, computers moved
        elif line[0] == 'q': # query, are the computers in same graph component
            if su == sv: right += 1
            else: wrong += 1
    if case != 0: print()
    print(right,',',wrong,sep='')
