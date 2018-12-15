import sys

case = 0
for line in sys.stdin:
    case += 1
    n, m, c = map(int,line.split())
    if n == m == c == 0: break
    print('Sequence %d'%case)
    # m operations, c amps limit, n devices
    devs = list(int(input()) for z in range(n)) # amps for each device
    devstates = [False]*n # power state
    power = 0 # amps drawn
    powermax = 0
    blown = False # is fuse blown
    for z in range(m): # perform operations
        dev = int(input())
        assert 1 <= dev <= n
        dev -= 1
        if devstates[dev]: # on
            devstates[dev] = False
            power -= devs[dev]
        else: # off
            devstates[dev] = True
            power += devs[dev]
            powermax = max(powermax,power)
        if power > c: blown = True
    if blown: print('Fuse was blown.\n')
    else:
        print('Fuse was not blown.')
        print('Maximal power consumption was %d amperes.\n'%powermax)

