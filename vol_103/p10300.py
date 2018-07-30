
n = int(input())
assert n < 20

for z in range(n):
    f = int(input())
    assert 0 < f < 20
    total = 0
    for zz in range(f):
        sqmeters, animals, envirofriendly = map(int,input().split())
        # money = (area / animals)*(e-friendly)*animals
        total += sqmeters*envirofriendly
    print(total)
