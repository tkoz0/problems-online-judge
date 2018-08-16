
nmax = 16
primes = set([2,3,5,7,11,13,17,19,23,29,31])

# index i: list of each ring (as a list)
rings = list([] for z in range(1+nmax))

ring = []
nums = set()
def recurse():
    global ring, nums, primes
    if len(nums) == 0: # used all nums in ring
        if (ring[0]+ring[-1]) in primes: # 2 ends link into a ring
            rings[len(ring)].append(ring[:])
    else:
        for nextnum in list(nums):
            if (ring[-1]+nextnum) in primes: # links with previous
                ring.append(nextnum)
                nums.remove(nextnum)
                recurse()
                nums.add(nextnum) # backtrack
                ring.pop()

for n in range(1,1+nmax):
    ring = [1]
    nums = set(range(2,1+n))
    recurse()
    rings[n].sort() # lexicographic ordering

case = 0
while True:
    case += 1
    try: n = int(input())
    except EOFError: break
    assert 0 < n <= nmax
    if case != 1: print()
    print('Case %d:'%case)
    for r in rings[n]: print(' '.join(str(z) for z in r))
