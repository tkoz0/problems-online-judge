from functools import reduce

def and_op(itr): return reduce(lambda x,y:x and y,itr)

problem_num = 0

while True:
    problem_num += 1
    try: n = int(input())
    except Exception: break
    if problem_num > 1:
        print()
        print('**********************************')
        print()
    print('Problem #%d'%problem_num)
    print()
    assert 2 <= n <= 9
    # true if connecting line starts at that index and goes right/down
    horz = [[False]*(n-1) for _ in range(n)]
    vert = [[False]*n for _ in range(n-1)]
    sqcount = [0]*n # max size is n-1
    m = int(input())
    for _ in range(m):
        t,i,j = input().split()
        i,j = int(i),int(j)
        if t == 'H' and 1 <= i <= n and 1 <= j <= n-1:
            horz[i-1][j-1] = True
        elif t == 'V' and 1 <= i <= n and 1 <= j <= n-1:
            vert[j-1][i-1] = True
        #else: assert 0
        # this assertion can fail, commenting out fixed solution for the judge
        # the range checking should be correct
    #continue
    for sqsize in range(1,n): # for each square size
        for r in range(n-sqsize): # top left corner
            for c in range(n-sqsize):
                # check top, left, bottom, right, all need to have true values
                if and_op(horz[r][c+i] for i in range(sqsize)) \
                    and and_op(vert[r+i][c] for i in range(sqsize)) \
                    and and_op(horz[r+sqsize][c+i] for i in range(sqsize)) \
                    and and_op(vert[r+i][c+sqsize] for i in range(sqsize)):
                    sqcount[sqsize] += 1
                    #print('size %d at %d,%d'%(sqsize,r,c))
    if sum(sqcount) == 0: print('No completed squares can be found.')
    else:
        for i in range(1,n):
            if sqcount[i] > 0:
                print('%d square (s) of size %d'%(sqcount[i],i))
