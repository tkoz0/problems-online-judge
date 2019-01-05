import math
import functools

T = int(input())
assert T <= 110

def area(vecs): # return double the area
    # vector triangles + rest of area
    return sum(vec[0]*vec[1] for vec in vecs) \
        + 2*sum(vecs[i][0] * sum(vecs[j][1] for j in range(i))
            for i in range(len(vecs)))

def veccmp(a,b):
    m1 = a[1]/a[0] if a[0] != 0 else math.inf # compute slopes
    m2 = b[1]/b[0] if b[0] != 0 else math.inf
    if m1 < m2: return 1
    if m1 > m2: return -1
    mag1 = math.sqrt(a[0]**2+a[1]**2)
    mag2 = math.sqrt(b[0]**2+b[0]**2)
    if mag1 < mag2: return 1
    else: return -1

for case in range(1,1+T):
    N, K = map(int,input().split())
    assert 1 <= K <= N <= 50
    # N input vectors, must pick K to maximize area
    vecs = []
    for _ in range(N):
        vec = tuple(map(int,input().split()))
        assert 0 <= vec[0] <= 50
        assert 0 <= vec[1] <= 50
        vecs.append(vec)
    # sort by slope in decreasing order
    vecs.sort(key=functools.cmp_to_key(veccmp))
    # if vectors selection is known, order must be convex (visualize it)

    # while too many vectors, take out the one that minimizes area loss
    while len(vecs) > K:
        loss = [] # loss of area for removing that vector
        for i in range(len(vecs)):
            loss.append(vecs[i][0]*vecs[i][1] # vector triangle
                + 2 * vecs[i][0] * sum(vecs[j][1] # vertical column
                    for j in range(i))
                + 2 * vecs[i][1] * sum(vecs[j][0] # horizontal row
                    for j in range(i+1,len(vecs))))
        i = 0 # vector that minimizes losses
        for j in range(1,len(loss)):
            if loss[j] < loss[i]: i = j
        vecs.pop(i) # remove this vector

    print('Case %d: %d'%(case,area(vecs)))

