import sys

W = 60 # width for output

for line in sys.stdin:
    N = int(line)
    assert 1 <= N <= 100
    files = []
    for z in range(N): files.append(input())
    print('-'*W)
    files = sorted(files)
    w = max(len(f) for f in files) # column width based on longest file name
    c = (W+2) // (w+2) # number of rows and columns to use for printing
    r = (len(files) // c) + (1 if (len(files) % c != 0) else 0)
    out = ['']*r # text in each row
    fstr = '%-' + str(w) + 's' # print file names with width, left justified
    for i,f in enumerate(files): # go column by column placing files
        out[i % r] += (fstr % f) + '  ' # include 2 spaces
    for l in out: print(l[:-2]) # exclude ending 2 spaces
