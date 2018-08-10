
# dynamic programming
ways = [1,1] # 1 way for 0 and 1 length walls
while len(ways) <= 50:
    # if placing 1 vertical, fill n-1 wide remaining, 2 horizontal: n-2 wide
    ways.append(ways[-1]+ways[-2])
# this just generates the fibonacci sequence

while True:
    n = int(input())
    if n == 0: break
    assert n <= 50
    print(ways[n])
