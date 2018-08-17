
T = int(input())

for z in range(T):
    pages = dict() # map relevance to pages
    for zz in range(10):
        line = input().split()
        if not (int(line[1]) in pages): pages[int(line[1])] = []
        pages[int(line[1])].append(line[0])
    print('Case #%d:'%(z+1))
    for p in pages[max(pages.keys())]: print(p)
