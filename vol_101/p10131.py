import sys

elephants = []
num = 0
for line in sys.stdin:
    num += 1
    kg, iq = map(int,line.split())
    assert 1 <= kg <= 10000
    assert 1 <= iq <= 10000
    elephants.append((kg,iq,num))
assert len(elephants) <= 1000

elephants = sorted(elephants) # sort by weight (increasing)
longest = [0]*len(elephants) # longest possible seq starting here
enext = [0]*len(elephants) # next elephant in longest sequence, 0 terminates

# dynamic solution, work backwards, pick optimal next elephant
for i in range(len(elephants)-2,-1,-1):
    bestl = 0 # default to nothing after
    bestj = 0 # default to terminate at index i
    j = len(elephants)-1 # index of next elephant
    while elephants[j][0] > elephants[i][0]: # has larger weight
        if longest[j] > bestl and elephants[j][1] < elephants[i][1]:
            # longest sequence, iq decreasing
            bestl = longest[j]
            bestj = j
        elif longest[j] == bestl and elephants[j][1] < elephants[i][1] \
            and elephants[j][2] < elephants[bestj][2]:
            bestj = j
        j -= 1
    enext[i] = bestj
    longest[i] = 1+bestl # include index i itself

# find optimal start
besti = 0
bestl = longest[0]
for i in range(1,len(elephants)):
    if longest[i] > bestl:
        bestl = longest[i]
        besti = i
    # pick lexicographically smallest sequence
    elif longest[i] == bestl and elephants[besti][2] < elephants[i][2]:
        besti = i

print(bestl) # length
while besti != 0: # print sequence (original indexes in input)
    print(elephants[besti][2])
    besti = enext[besti]
