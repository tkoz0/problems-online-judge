
while True:
    sentence = input()
    if sentence == 'DONE': break
    letters = ''
    for c in sentence.lower():
        if c in 'abcdefghijklmnopqrstuvwxyz': letters += c
    print('You won\'t be eaten!' if letters == letters[::-1] else 'Uh oh..')
