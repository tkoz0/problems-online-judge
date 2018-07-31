import sys

for line in sys.stdin:
    cigs, k = map(int,line.split())
    assert k > 1
    allcigs = 0
    butts = 0
    while cigs != 0:
        allcigs += cigs
        butts += cigs
        cigs, butts = divmod(butts,k)
    print(allcigs)
