
puzzlenum = 0
while True:
    puzzlenum += 1
    puz = []
    for z in range(5):
        try: puz.append(list(input()))
        except EOFError: break
    if len(puz) != 5: break # reached end of input
    assert len(puz) == 5
    for z in puz: assert len(z) == 5, z
    moves = ''
    while True: # read move sequence until encountering the '0'
        moves += input()
        if moves[-1] == '0': break
    br, bc = -1, -1 # blank position
    for r in range(5):
        for c in range(5):
            if puz[r][c] == ' ':
                assert br == bc == -1 # only instance
                br, bc = r, c
    assert br != -1 and bc != -1 # space must exist
    if puzzlenum != 1: print()
    print('Puzzle #%d:'%puzzlenum)
    invalid = False # if invalid move occurs (no final configuration)
    for m in moves:
        if m == 'A': # br-1
            if br == 0: invalid = True; break
            else: # swap and adjust blank position
                puz[br][bc], puz[br-1][bc] = puz[br-1][bc], puz[br][bc]
                br -= 1
        elif m == 'B': # br+1
            if br == 4: invalid = True; break
            else:
                puz[br][bc], puz[br+1][bc] = puz[br+1][bc], puz[br][bc]
                br += 1
        elif m == 'L': # bc-1
            if bc == 0: invalid = True; break
            else:
                puz[br][bc], puz[br][bc-1] = puz[br][bc-1], puz[br][bc]
                bc -= 1
        elif m == 'R': # bc+1
            if bc == 4: invalid = True; break
            else:
                puz[br][bc], puz[br][bc+1] = puz[br][bc+1], puz[br][bc]
                bc += 1
#        else: assert m == '0'
    if invalid: print('This puzzle has no final configuration.')
    else:
        for z in puz: print(' '.join(z))
