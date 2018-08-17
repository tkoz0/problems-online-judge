import math

while True:
    try:
        line = input().split()
        r, n = float(line[0]), int(line[1])
    except EOFError: break
    assert 0.0 < r < 20000.0
    assert 2 < n < 20000
    # region will have triangles with 2 sides r and 1 angle is a = (2pi/n rad)
    # divide the trangle into 2 right triangles to find height and half base
    # each triangle has area hb/2 = (r*cos(a/2))*(r*sin(a/2))
    # solution is n*(above expression)
    print('%.3f'%(n*(r**2)*math.sin(math.pi/n)*math.cos(math.pi/n)))
