
words = { 'one':1, 'two':2, 'three':3 }

def match(a,b):
    if len(a) != len(b): return False
    diffs = 0
    for i in range(len(a)):
        if a[i] != b[i]: diffs += 1
    return diffs <= 1

n = int(input())
for z in range(n):
    word = input()
    for w in words:
        if match(word,w): print(words[w])
