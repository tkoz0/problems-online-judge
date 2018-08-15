
cases = int(input())

def tuple_min(a,b): # upperleftmost coordinates
    if a[0] < b[0]: return a
    if a[0] > b[0]: return b
    return a if (a[1] < b[1]) else b

for z in range(cases):
    try: _space = input()
    except EOFError: break
    assert _space == '' # blank line between consecutive
    m, n = map(int,input().split()) # m rows, n cols
    grid = '' # store grid as a single string
    for zz in range(m):
        row = input()
        assert len(row) == n
        grid += row.lower()
    k = int(input()) # num words to search for
    if z != 0: print() # blank line between output for each case
    for zz in range(k):
        word = input().lower()
        found = (m,n) # upperleftmost instance of the word
        for r in range(m): # search rows
            row = grid[r*n:r*n+n]
            c = row.find(word) # right
            if c != -1: found = tuple_min(found,(r,c))
            c = row[::-1].find(word) # left
            if c != -1: found = tuple_min(found,(r,n-1-c))
        for c in range(n): # search cols
            col = grid[c::n]
            r = col.find(word) # down
            if r != -1: found = tuple_min(found,(r,c))
            r = col[::-1].find(word) # up
            if r != -1: found = tuple_min(found,(m-1-r,c))
        for rs in range(m): # down right diagonal, start on left
            r, c = rs, 0
            line = ''
            while r < m and c < n:
                line += grid[r*n+c]
                r, c = r+1, c+1
            i = line.find(word) # down right
            if i != -1: found = tuple_min(found,(rs+i,i))
            i = line[::-1].find(word) # up left
            if i != -1: found = tuple_min(found,
                                          (rs+len(line)-1-i,len(line)-1-i))
        for cs in range(n): # down right diagonal, start on top
            r, c = 0, cs
            line = ''
            while r < m and c < n:
                line += grid[r*n+c]
                r, c = r+1, c+1
            i = line.find(word) # dowr right
            if i != -1: found = tuple_min(found,(i,cs+i))
            i = line[::-1].find(word) # up left
            if i != -1: found = tuple_min(found,
                                          (len(line)-1-i,cs+len(line)-1-i))
        for rs in range(m): # up right diagonal, start on left
            r, c = rs, 0
            line = ''
            while r >= 0 and c < n:
                line += grid[r*n+c]
                r, c = r-1, c+1
            i = line.find(word) # up right
            if i != -1: found = tuple_min(found,(rs-i,i))
            i = line[::-1].find(word) # down left
            if i != -1: found = tuple_min(found,
                                          (rs-len(line)+1+i,len(line)-1-i))
        for cs in range(n): # up right diagonal, start on bottom
            r, c = m-1, cs
            line = ''
            while r >= 0 and c < n:
                line += grid[r*n+c]
                r, c = r-1, c+1
            i = line.find(word) # up right
            if i != -1: found = tuple_min(found,(m-1-i,cs+i))
            i = line[::-1].find(word) # down left
            if i != -1: found = tuple_min(found,
                                          (m-1-len(line)+1+i,cs+len(line)-1-i))
        assert found != (m,n) # word must exist in grid
        print(found[0]+1,found[1]+1)
