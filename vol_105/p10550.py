
while True:
    init, n1, n2, n3 = map(int,input().split())
    if init == n1 == n2 == n3 == 0: break
    deg = 720 # 2 full clockwise
    deg += 9*((init-n1)%40) # num 1
    deg += 360 # 1 counterclockwise
    deg += 9*((n2-n1)%40) # num 2
    deg += 9*((n2-n3)%40) # num 3
    print(deg)
