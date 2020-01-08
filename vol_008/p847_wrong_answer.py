
def winner(n):
    p = 1
    stan = False
    while p < n:
        stan = not stan
        if p * 9 >= n: p *= 9 # can win here, so do that
        else:
            # multiply largest possible so that next player cant win immediately
            # (n+8)//9 is largest integer we will allow p to reach at first
            desired_pick = min(9,(n+8)//9//p)
            if desired_pick < 2: desired_pick = 2 # have to pick in range
            p *= desired_pick
        #print('%8s: %d'%('Stan' if stan else 'Ollie',p))
    return 'Stan' if stan else 'Ollie'

import sys
for line in sys.stdin: print('%s wins.'%winner(int(line)))
