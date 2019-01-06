import sys

while True:
    grid = [] # 2d array of characters
    end_line = ''
    reach_eof = False
    while True: # read input lines
        try: line = input()
        except EOFError:
            reach_eof = True
            break
        if set(line) == set('_'):
            end_line = line
            break
        grid.append(list(line))
    if reach_eof: break
    marked = [] # mark visited locations in flood fill
    for r in grid:
        marked.append([False]*len(r))
    contour = '' # find edge character used for contours
    for r in grid:
        found = False
        for c in r:
            if c != '_' and c != ' ':
                contour = c
                found = True
                break
        if found: break
    assert contour != ''
    for r in range(len(marked)): # perform region filling
        for c in range(len(marked[r])):
            if marked[r][c]: continue # already part of a filled region
            if grid[r][c] == contour: continue # not inside a region
            stack = [(r,c)] # grid positions to search, iterative DFS
            marking_char = '' # the non space char in this region
            region = set() # positions in this region
            while len(stack): # this should not mark the contours
                rr, cc = stack.pop()
                if rr < 0 or rr >= len(marked) \
                    or cc < 0 or cc >= len(marked[rr]): # out of bounds
                    continue
                if grid[rr][cc] == contour: continue # edge of region
                if marked[rr][cc]: continue # was already marked
                if grid[rr][cc] != ' ': # found marking char
                    if marking_char == '': marking_char = grid[rr][cc]
                    else: assert grid[rr][cc] == marking_char
                marked[rr][cc] = True # mark visited cell
                region.add((rr,cc)) # position in current region
                # DFS to adjacent cells
                stack += [(rr+1,cc),(rr,cc+1),(rr-1,cc),(rr,cc-1)]
            if marking_char == '': continue # unmarked region
            else: # fill region
                for r,c in region:
                    grid[r][c] = marking_char
    # print results
    for r in grid:
        print(''.join(r))
    print(end_line)

