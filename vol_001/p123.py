ignore = set()

import sys
for line in sys.stdin:
    if line.strip() == '::': break
    ignore.add(line.strip().lower()) # should be given in lowercase
assert(len(ignore) <= 50)

kwmap = dict() # map keyword to titles with it
titles = []
titlei = dict() # title --> index (input order)

for title in sys.stdin:
    title = title.strip()
    titles.append(title)
    titlei[title] = len(titles)-1
    words = [w.lower() for w in title.split()]
    for w in words:
        if w in ignore: continue
        if not (w in kwmap): kwmap[w] = set()
        kwmap[w].add(title)

for kw in sorted(kwmap.keys()):
    # sort titles by input order
    for t in sorted(kwmap[kw],key=lambda x:titlei[x]):
        twords = [w.lower() for w in t.split()]
        for i,w in enumerate(twords): # for each occurence of the keyword
            if w != kw: continue # skip non keyword
            twords[i] = w.upper() # make uppercase for printing
            print(' '.join(twords))
            twords[i] = w.lower()
