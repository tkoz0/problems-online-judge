
def evaluate(r,c,marked,eval,spreadsheet): # true if evaluation successful
    if marked[r][c]: return type(eval[r][c]) == int
    marked[r][c] = True # mark and recursively try to evaluate
    if type(spreadsheet[r][c]) == int:
        eval[r][c] = spreadsheet[r][c]
        return True # base integer "evaluates"
    else: # must parse and evaluate
        cell = spreadsheet[r][c]
        assert type(cell) == str
        split1 = cell.split('+')
        split2 = [split1[0]] + sum([['+',v] for v in split1[1:]],[]) # include +
        split3 = []
        for expr in split2:
            spl = expr.split('-')
            spl1 = [spl[0]] + sum([['-',v] for v in spl[1:]],[]) # include -
            split3 += spl1
        split3 = [v.strip() for v in split3]
#        print('evaluate',r,c,split3)
        # evaluate split 3 from left to right
        assert len(split3) % 2 == 1
        while len(split3) > 2: # index 1 contains on operator
            left = split3[0]
            try: left = int(left) # is integer
            except Exception: # must evaluate cell
                rr = ord(left[0])-ord('A')
                cc = int(left[1])
                if not evaluate(rr,cc,marked,eval,spreadsheet): return False
                left = eval[rr][cc]
            right = split3[2]
            try: right = int(right) # is integer
            except Exception: # must evaluate cell
                rr = ord(right[0])-ord('A')
                cc = int(right[1])
                if not evaluate(rr,cc,marked,eval,spreadsheet): return False
                right = eval[rr][cc]
            if split3[1] == '+': split3[:3] = [left+right]
            elif split3[1] == '-': split3[:3] = [left-right]
            else: assert 0
        if type(split3[0]) == str: # must evaluate single cell reference
            rr = ord(split3[0][0])-ord('A')
            cc = int(split3[0][1])
            if not evaluate(rr,cc,marked,eval,spreadsheet): return False
            eval[r][c] = eval[rr][cc]
            return True
        else:
            assert type(split3[0]) == int
            eval[r][c] = split3[0]
            return True

while True:
    R,C = map(int,input().split())
    if R == 0 and C == 0: break # eof
    assert 1 <= R <= 20 and 1 <= C <= 10
    # rows are A through T, columns are 0 through 9
    alphabet = 'ABCDEFGHIJKLMNOPQRST'
    spreadsheet = [[None]*C for _ in range(R)]
    marked = [[False]*C for _ in range(R)]
    for r in range(R):
        for c in range(C):
            cell = input()
            try: spreadsheet[r][c] = int(cell)
            except Exception: spreadsheet[r][c] = cell
    eval = [[None]*C for _ in range(R)] # evaluated calculations
    cyclic = [] # list of (r,c) pairs that cant evaluate (cyclic reference)
    stack = [] # perform DFS on unmarked cells to evaluate
    for r in range(R):
        for c in range(C):
            if not evaluate(r,c,marked,eval,spreadsheet):
                cyclic.append((r,c))
    if len(cyclic) > 0:
        for r,c in sorted(cyclic):
            print('%s%d: %s'%(alphabet[r],c,spreadsheet[r][c]))
    else: # all evaluated successfully
        print(' '+''.join('%6d'%c for c in range(C)))
        for r in range(R):
            print(alphabet[r]+''.join('%6d'%eval[r][c] for c in range(C)))
    print()
