import sys

num_games = int(input())

def count(board,char): return sum(row.count(char) for row in board)

# any pieces bracketed in a line, dr,dc determine stepping direction
def bracket_line(board,white,r,c,dr,dc):
    other_color = False # whether it was found on the path
    while True:
        r += dr
        c += dc
        if r < 0 or r >= 8 or c < 0 or c >= 8: return False # bounds check
        if board[r][c] == '-': return False
        if board[r][c] == ('B' if white else 'W'): other_color = True
        if board[r][c] == ('W' if white else 'B'):
            # must have found other color along path before this
            return other_color

def legal(board,white,r,c): # must bracket pieces in at least 1 of the 8 lines
    if board[r][c] != '-': return False
    for dr,dc in [(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1),(0,1),(1,1)]:
        if bracket_line(board,white,r,c,dr,dc): return True
    return False

def legal_moves(board,white):
    movelist = []
    for r in range(8):
        for c in range(8):
            if legal(board,white,r,c): movelist.append((r,c))
    return movelist

def fill_line(board,white,r,c,dr,dc):
    if bracket_line(board,white,r,c,dr,dc):
        while True:
            r += dr
            c += dc
            if board[r][c] == ('W' if white else 'B'): return # reach end
            board[r][c] = ('W' if white else 'B')

def make_move(board,white,r,c):
    board[r][c] = ('W' if white else 'B')
    for dr,dc in [(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1),(0,1),(1,1)]:
        fill_line(board,white,r,c,dr,dc)

for g in range(num_games): # process each game
    board = []
    for z in range(8): board.append(list(sys.stdin.readline()[:-1]))
    white_turn = sys.stdin.readline()[:-1] == 'W' # current player
    while True:
        command = sys.stdin.readline()[:-1] # ignore \n
        if command == 'L': # list all possible moves (current player)
            # (print in row major order)
            moves = legal_moves(board,white_turn)
            if len(moves) == 0: print('No legal move.')
            else:
                print('(%d,%d)' % (moves[0][0]+1,moves[0][1]+1),end='')
                for z in range(1,len(moves)):
                    print(' (%d,%d)' % (moves[z][0]+1,moves[z][1]+1),end='')
                print()
        elif command[0] == 'M': # make move
            mr = int(command[1])-1 # position to move
            mc = int(command[2])-1
            # move current player unless current player has no legal moves
            # move can be assumed to be legal
            moves = legal_moves(board,white_turn)
            if len(moves) == 0: # must move other player
                white_turn = not white_turn
                moves = legal_moves(board,white_turn)
            assert (mr,mc) in moves # can assume it is valid
            make_move(board,white_turn,mr,mc)
            white_turn = not white_turn # switch player after making turn
            print('Black - %2d White - %2d'%(count(board,'B'),count(board,'W')))
        else: # quit this game
            assert command == 'Q'
            for l in board: print(''.join(l)) # final board configuration
            if g != num_games-1: print() # blank line separator
            break
