
while True:
    H1,M1,H2,M2 = map(int,input().split())
    assert 0 <= min(H1,H2) and max(H1,H2) < 24
    assert 0 <= min(M1,M2) and max(M1,M2) < 60
    if H1 == M1 == H2 == M2 == 0: break
    print((60*((H2-H1)%24)+(M2-M1))%1440)
