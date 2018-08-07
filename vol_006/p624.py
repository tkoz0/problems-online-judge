
while True:
    try: line = input()
    except EOFError: break
    line = list(map(int,line.split()))
    N = line[0]
    numtracks = line[1]
    tracks = line[2:]
    possibilities = [[]]*(N+1) # index i: tracks that sum to i minutes
    for track in tracks:
        assert track <= N
        for presum in range(N-track,-1,-1):
            # impossible to start with this sum before adding track
            if possibilities[presum] == []: continue
            if possibilities[presum+track] != []: continue # already found one
            possibilities[presum+track] = possibilities[presum]+[track]
        possibilities[track] = [track]
    i = N # number of minutes to use, find most minutes possible
    while i >= 0 and possibilities[i] == []: i -= 1
    # ignoring i=-1 possibility
    print(' '.join(str(z) for z in possibilities[i]), 'sum:%d' % i)
