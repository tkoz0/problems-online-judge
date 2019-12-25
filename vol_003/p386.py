
cubes = [a*a*a for a in range(1+200)]
cubeset = set(cubes)
cube2a = dict()
for i,cube in enumerate(cubes): cube2a[cube] = i
sets = []
for b in range(2,200):
    for c in range(b,200):
        for d in range(c,200):
            if (b**3 + c**3 + d**3) in cubeset:
                sets.append((cube2a[b**3+c**3+d**3],b,c,d))
#print('total %d sets'%len(sets))
sets = sorted(sets)
for s in sets:
    print('Cube = %d, Triple = (%d,%d,%d)'%s)
