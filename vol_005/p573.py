
while True:
    H, U, D, F = map(float,input().split())
    if H == 0.0: break
    assert 1.0 <= H <= 100.0
    assert 1.0 <= U <= 100.0
    assert 1.0 <= D <= 100.0
    assert 1.0 <= F <= 100.0
    h = 0.0
    climb = U
    day = 0
    while True:
        day += 1
        h += climb
        climb = max(0.0,climb-(F/100.0)*U)
        if h > H: break
        h -= D
        if h < 0.0: break
    print('success' if h > H else 'failure', 'on day', day)
