import sys

def get_nums(): # return all integers from stdin
    for line in sys.stdin:
        for n in map(int,line.split()): yield n

nums = dict() # map numbers to occurrences
inseq = [] # order they appeared in input
for n in get_nums():
    if n in nums: nums[n] += 1
    else: # new number
        inseq.append(n)
        nums[n] = 1
for n in inseq: print(n,nums[n])
