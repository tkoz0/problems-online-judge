import sys

collec = 0
for line in sys.stdin:
    collec += 1
    marbles = list(map(int,line.split()))
    assert sum(marbles) <= 20000
    marbles = list(m%2 for m in marbles)
    if sum(marbles) == 0: break # all zeroes ends input
    # WRONG, considerd the 5 marbles 6,4,4,3,3 as a counterexample
    # begin by taking even amounts of each marble away since they divide evenly
    msum = sum(i+1 for i in range(6) if marbles[i] == 1)
    print('Collection #%d:'%collec)
    if msum % 2 != 0: print("Can't be divided.")
    else: # find if msum/2 marbles is possible
        possible = [False]*(1+msum)
        possible[0] = True
        for i,m in enumerate(marbles):
            if m == 1: # this marble is present, value is i+1
                for j in range(msum-i-1,-1,-1):
                    if possible[j]: possible[j+i+1] = True
        if possible[msum//2]: print('Can be divided.')
        else: print("Can't be divided.")
    print()
