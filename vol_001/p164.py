import sys

limit = 99

dp = [[0]*(limit+1) for i in range(limit+1)]
back = [[None]*(limit+1) for i in range(limit+1)]
# from i,j, these values determine what to do
# 1 - characters equal, go to i-1,j-1
# 2 - delete init(i), go to i-1,j
# 3 - insert goal(j), go to i,j-1
# 4 - substitute init(i) with goal(j), go to i-1,j-1

for line in sys.stdin:
    try: init, goal = line.split()
    except Exception: break
    assert len(init) <= limit and len(goal) <= limit

    # base case edit distances
    dp[0][0] = 0
    for i in range(1,1+len(init)):
        dp[i][0] = i
        back[i][0] = 2
    for j in range(1,1+len(goal)):
        dp[0][j] = j
        back[0][j] = 3

    # fill in dp table
    for i in range(1,1+len(init)):
        for j in range(1,1+len(goal)):
            if init[i-1] == goal[j-1]:
                back[i][j] = 1
                dp[i][j] = dp[i-1][j-1]
            else: # pick best of 3 choices
                dp[i][j] = 1+min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])
                # find which path for backtracking
                if 1+dp[i-1][j] == dp[i][j]: back[i][j] = 2
                elif 1+dp[i][j-1] == dp[i][j]: back[i][j] = 3
                else: back[i][j] = 4

    # construct solution
    s_init = ''
    s_goal = ''
    i,j = len(init),len(goal)
    while i > 0 or j > 0:
        if back[i][j] == 1:
            assert i>0 and j>0
            s_init += init[i-1]
            s_goal += goal[j-1]
            i,j = i-1,j-1
        elif back[i][j] == 2:
            assert i>0
            s_init += init[i-1]
            s_goal += ' '
            i,j = i-1,j
        elif back[i][j] == 3:
            assert j>0
            s_init += ' '
            s_goal += goal[j-1]
            i,j = i,j-1
        else:
            assert i>0 and j>0
            s_init += init[i-1]
            s_goal += goal[j-1]
            i,j = i-1,j-1
    assert i == 0 and j == 0
    s_init = s_init[::-1]
    s_goal = s_goal[::-1]

#    print(s_init)
#    print(s_goal)

    p = 1 # position for operations
    for i in range(len(s_init)):
        if s_init[i] == s_goal[i]: p += 1
        elif s_init[i] == ' ': # insertion, go to next char
            print('I%s%02d'%(s_goal[i],p),end='')
            p += 1
        elif s_goal[i] == ' ': # deletion, keep same p
            print('D%s%02d'%(s_init[i],p),end='')
        else: # change, go to next char
            print('C%s%02d'%(s_goal[i],p),end='')
            p += 1
    print('E')

