
T = int(input())
assert 1 <= T <= 100

money = 0
for z in range(T):
    args = input().split()
    if args[0] == 'report': print(money)
    else:
        assert args[0] == 'donate'
        money += int(args[1])
