
while True:
    N = int(input())
    if N == 0: break
    assert 0 < N < 13
    lines = []
    for z in range(N):
        line = input()
        assert len(line) == 25 and line[0] == 'X' and line[-1] == 'X'
        lines.append(line.count(' '))
    # can move min(lines) times before contact
    print(sum(lines) - len(lines)*min(lines))
