import sys

alpha = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'

counter = 0
for line in sys.stdin:
    counter += 1
    K, E = map(int,line.split())
    assert 1 <= K <= 20
    assert 1 <= E <= 20
    keywords = []
    for z in range(K): keywords.append(input().lower())
    excuses = []
    for z in range(E): excuses.append(input())
    incidences = [0]*len(excuses) # count how many times keywords appear in them
    for kw in keywords:
        for i,excuse in enumerate(excuses):
            excuse = excuse.lower() # ignore case when searching keywords
            # start at alphanumeric chars in excuse and compare to keyword
            for ei in range(len(excuse)):
                if ei == 0 or (not (excuse[ei-1] in alpha)):
                    esub = excuse[ei:]
                    if esub.startswith(kw) and (len(esub)==len(kw) or \
                                                (not (esub[len(kw)] in alpha))):
                        incidences[i] += 1
    worst = max(incidences)
    print('Excuse Set #%d' % counter)
    for i,e in enumerate(excuses):
        if incidences[i] == worst: print(e)
    print()
