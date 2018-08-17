
index = 1
words = dict() # map word to index
letters = 'abcdefghijklmnopqrstuvwxyz'
def recurse(w,i,l):
    global index, words, letters
    if len(w) == l:
        words[w] = index
        index += 1
    else:
        for z in range(i,26): recurse(w+letters[z],z+1,l)
for z in range(1,1+5): recurse('',0,z)

while True:
    try: print(words[input()])
    except KeyError: print('0')
    except EOFError: break
