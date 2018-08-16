
while True:
    N = int(input())
    if N <= 0: break
    # paid 4pi*r^2 for the sphere
    # each part will have 4pi*r^2/N + pi*r^2 (semicircles)
    # total surface area is pi*r^2*(4+N) so ratio is 4+N to 4
    # profit is ((4+N)-4)/4 (gain / initial) or N/4 or 25*N %
    if N > 1: print('%d%%'%(25*N))
    else: print('0%') # exception is 1 piece (no profit)
