
lowerletters = 'abcdefghijklmnopqrstuvwxyz'

while True:
    try: a = input(); b = input()
    except EOFError: break
    # put as many instances of each letter as minimum of its count in a and b
    print(''.join(l*min(a.count(l),b.count(l)) for l in lowerletters))
