
cases = int(input())

for _ in range(cases):
    F = int(input())
    people = dict() # map name to component id
    components = [[]] # people in components
    next_component = 1
    for __ in range(F):
        a,b = input().split()
        if a in people: ca = people[a]
        else: ca = 0
        if b in people: cb = people[b]
        else: cb = 0
        if ca == cb == 0: # new component
            people[a] = next_component
            people[b] = next_component
            components.append([a,b])
            next_component += 1
            print(2)
        elif ca == 0: # add to component with b
            people[a] = cb
            components[cb].append(a)
            print(len(components[cb]))
        elif cb == 0:
            people[b] = ca
            components[ca].append(b)
            print(len(components[ca]))
        # both in existing components
        elif ca == cb: print(len(components[ca])) # doesnt increase component size
        else: # need to merge components
            # move smaller number of people to target component
            source = ca if len(components[ca]) < len(components[cb]) else cb
            target = ca if source == cb else cb
            for p in components[source]: # move to new component
                people[p] = target
            components[target] += components[source]
            components[source] = [] # empty now
            print(len(components[target]))
