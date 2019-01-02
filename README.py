import time
import sys

# For generating the readme file with the problem list

print('UVa Online Judge')
print('List of Solved Problems')
print('Last updated',time.strftime('on %Y-%m-%d at %H-%M-%S'))
print()
print('Problems are separated by volume, organized into a grid for each.')
print('Row is tens digit and column in ones digit.')
print('A * next to the number indicates that the problem was solved.')
print()

# Read problems from sys.stdin

problems = set()

for line in sys.stdin:
    for problem in map(int,line.split()):
        problems.add(problem)

volumes = set() # list of volumes from which at least 1 problem was solved
results = dict() # map volume to 2d grid of booleans for solved status
# each grid is 10x10, index by row=tens and col=ones

for problem in problems:
    vol = problem//100
    pnum = problem%100
    if not (vol in volumes): # must create volume
        volumes.add(vol)
        results[vol] = [[False]*10 for _ in range(10)]
    results[vol][pnum//10][pnum%10] = True

# output results

for volume in sorted(volumes): # print results in sorted order
    print('Volume %3d:'%volume)
    print()
    for r in range(10):
        for c in range(10):
            if results[volume][r][c]: print(' *%d%d'%(r,c),end='')
            else: print('  %d%d'%(r,c),end='')
        print()
    print()

