
while True:
    a, b = map(int,input().split())
    if a == -1 and b == -1: break
    assert 0 <= a <= 99
    assert 0 <= b <= 99
    dif = abs(a-b)
    print(min(dif,100-dif))
