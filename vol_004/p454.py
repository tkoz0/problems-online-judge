
cases = int(input())
assert input() == ''

for _ in range(cases):
    phrases = []
    while True:
        try: line = input()
        except EOFError: break
        if line == '' or set(line) == set(' '): break
        phrases.append(line)
    phrases = sorted(phrases)
    sortstrs = []
    for i,phrase in enumerate(phrases):
        sortstrs.append(sorted(c for c in phrase if c != ' '))
    if _: print()
    for i in range(len(phrases)):
        for j in range(i+1,len(phrases)):
            if sortstrs[i] == sortstrs[j]:
                print(phrases[i],'=',phrases[j])

