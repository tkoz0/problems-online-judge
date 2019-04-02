import sys

cost = [[0]*250 for i in range(250)] # dp optimal cost
quer = [[0]*250 for i in range(250)] # dp queries count

for line in sys.stdin:
    f = list(map(int,line.split()))
    f = f[1:] # remove size indicator at beginning
    n = len(f)
    assert n <= 250

    # cost[i][j] = cost for optimal tree made on elements i to j (inclusive)
    for i in range(n):
        cost[i][i] = 0
        quer[i][i] = f[i]
    for d in range(1,n): # distance between endpoints on range
        for i in range(n-d):
            j = i+d
            # try left as root
            # cost is 1 extra edge for each query + cost of subtree
            cost[i][j] = quer[i+1][j] + cost[i+1][j]
            # include queries for root in count
            quer[i][j] = f[i] + quer[i+1][j]
            # try right as root
            if quer[i][j-1] + cost[i][j-1] < cost[i][j]:
                cost[i][j] = quer[i][j-1] + cost[i][j-1]
                quer[i][j] = f[j] + quer[i][j-1]
            # try middles
            for m in range(i+1,j): # subtrees [i,m-1] and [m+1,j]
                # 1 extra edge for each query within subtrees
                cost_ = quer[i][m-1] + cost[i][m-1] + \
                        quer[m+1][j] + cost[m+1][j]
                if cost_ < cost[i][j]:
                    cost[i][j] = cost_
                    quer[i][j] = f[m] + quer[i][m-1] + quer[m+1][j]

    print(cost[0][n-1])

