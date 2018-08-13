
while True:
    round = int(input())
    if round < 0: break
    solution = input()
    guesses = input()
    print('Round',round)
    covered = set(solution) # correct letters not guessed yet
    guessed = set()
    hangman = 0
    game_done = False
    for guess in guesses:
        if guess in guessed: continue # no repeated guesses
        guessed.add(guess)
        if guess in covered: # correct
            covered.remove(guess)
            if len(covered) == 0: # win
                game_done = True
                print('You win.')
                break
        else: # wrong
            hangman += 1
            if hangman == 7: # lose
                game_done = True
                print('You lose.')
                break
    if not game_done: print('You chickened out.')
