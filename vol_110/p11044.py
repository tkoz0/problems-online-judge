
t = int(input())
for z in range(t):
    n, m = map(int,input().split())
    assert 6 <= n <= 10000
    assert 6 <= m <= 10000
    n -= 2 # since borders are unnecessary
    m -= 2
    sonars = (n//3)*(m//3) # largest grid with multiples of 3
    if m % 3 != 0: sonars += n//3 # fill edges
    if n % 3 != 0: sonars += m//3
    if m % 3 != 0 and n % 3 != 0: sonars += 1 # fill corner
    print(sonars)
