
n = int(input())

def order(c): # integer for character
    # capitals come before lowercase, interlace the sequences
    # A B C ...
    #  a b c ...
    if c <= 'Z': return 2 * (ord(c) - ord('A'))
    else: return 1 + 2 * (ord(c) - ord('a'))

for z in range(n):
    word = list(input())
    word.sort(key=lambda c:order(c))
    while True: # generate lexicographic order based on integers from order(c)
        print(''.join(word))
        i1 = len(word)-1
        while i1 != 0 and order(word[i1-1]) >= order(word[i1]): i1 -= 1
        i1 -= 1
        if i1 == -1: break # reached decreasing order
        i2 = len(word)-1 # find smallest later letter
        while order(word[i2]) <= order(word[i1]): i2 -= 1
        word[i1], word[i2] = word[i2], word[i1]
        i1 += 1 # reverse order
        i2 = len(word)-1
        while i1 < i2:
            word[i1], word[i2] = word[i2], word[i1]
            i1 += 1
            i2 -= 1
