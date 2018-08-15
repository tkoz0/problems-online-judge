
while True:
    line = input().split()
    G = int(line[0])
    if G == 0: break
    assert len(line[1]) % G == 0
    group = len(line[1])//G
    print(''.join(line[1][i*group:i*group+group][::-1] for i in range(G)))
