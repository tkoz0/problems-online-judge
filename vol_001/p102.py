import sys

orders = ['BCG', 'BGC', 'CBG', 'CGB', 'GBC', 'GCB'] # alphabetically sorted

for line in sys.stdin:
    # input order BGC BGC BGC (each of the 3 bins)
    n = list(map(int,line[:-1].split())) # extract integers
    moved = [0]*6 # amount moved for each of 6 possibilities
    # count moved amount in each configuration
    moved[0] = n[3] + n[6] + n[2] + n[8] + n[1] + n[4]
    moved[1] = n[3] + n[6] + n[1] + n[7] + n[2] + n[5]
    moved[2] = n[5] + n[8] + n[0] + n[6] + n[1] + n[4]
    moved[3] = n[5] + n[8] + n[1] + n[7] + n[0] + n[3]
    moved[4] = n[4] + n[7] + n[0] + n[6] + n[2] + n[5]
    moved[5] = n[4] + n[7] + n[2] + n[8] + n[0] + n[3]
    i = 0
    for j in range(1,6): # find min moved
        if moved[j] < moved[i]: i = j
    print(orders[i], moved[i]) # alphabetic minimum with min bottles moved
