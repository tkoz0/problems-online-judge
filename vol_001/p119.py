
first = True
while True:
    try: N = int(input()) # number of people
    except EOFError: break
    names = input().split()
    assert len(names) <= 10
    changes = dict() # map names to net worth change
    for name in names: changes[name] = 0
    for pnum in range(len(names)): # read line for each person
        line = input().split() # name, spent, num giving to, recipients...
        assert len(line) == 3+int(line[2])
        if len(line) == 3: continue # person does no gift giving
        pergift, kept = divmod(int(line[1]),int(line[2]))
        for name in line[3:]: changes[name] += pergift # +worth for recipients
        changes[line[0]] -= pergift*int(line[2]) # -worth for buying gifts
    if not first: print()
    for name in names: print(name,changes[name])
    first = False
