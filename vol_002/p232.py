
puzzle_num = 0
first_puzzle = True

while True:
    puzzle_num += 1
    try: r,c = map(int,input().split())
    except Exception: break # 0 line at end
    assert 1 <= r <= 10 and 1 <= c <= 10
    grid = [list(input()) for _ in range(r)]
    across = dict() # map number --> word
    down = dict()
    cell_num = 0
    for rr in range(r):
        for cc in range(c):
            if grid[rr][cc] == '*': continue
            cell_num_incremented = False
            if rr == 0 or grid[rr-1][cc] == '*': # down "eligible"
                word = ''
                for rrr in range(rr,r):
                    if grid[rrr][cc] == '*': break
                    word += grid[rrr][cc]
                cell_num += 1
                cell_num_incremented = True
                down[cell_num] = word
            if cc == 0 or grid[rr][cc-1] == '*': # across "eligible"
                word = ''
                for ccc in range(cc,c):
                    if grid[rr][ccc] == '*': break
                    word += grid[rr][ccc]
                if not cell_num_incremented: cell_num += 1
                across[cell_num] = word
    if first_puzzle: first_puzzle = False
    else: print() # separator
    print('puzzle #%d:'%puzzle_num);
    print('Across')
    for i in sorted(across.keys()): print('%3d.%s'%(i,across[i]))
    print('Down')
    for i in sorted(down.keys()): print('%3d.%s'%(i,down[i]))
