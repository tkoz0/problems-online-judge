import sys

# l[i] is rank for event i+1, convert to the chronological event order
def rankings_to_order(l):
    r = [0]*len(l)
    for i,v in enumerate(l): r[v-1] = i+1
    return r

n = int(input())
while True:
    assert 2 <= n <= 20
    correct = list(map(int,input().split()))
    assert len(correct) == n
    correct = rankings_to_order(correct)
    order = dict() # map event numbers to index in correct order
    for i,v in enumerate(correct): order[v] = i
    eof = True
    for line in sys.stdin: # read each student
        student = list(map(int,line.split()))
        if len(student) != n: n = student[0]; eof = False; break
        assert len(student) == n
        student = rankings_to_order(student)
        # compute longest with dynamic programming
        longest = [0]*len(student)
        for start in range(len(student)-1,-1,-1):
            most = 0
            for nexti in range(start+1,len(student)):
                if order[student[nexti]] > order[student[start]]:
                    most = max(most,longest[nexti])
            longest[start] = most+1
        print(max(longest))
    if eof: break
