
N = int(input())

for z in range(N):
    L = int(input())
    assert 0 <= L <= 50
    train = list(map(int,input().split()))
    # count swaps needed by insertion sort
    swaps = 0
    for select in range(1,len(train)):
        i = select
        while i != 0 and train[i-1] > train[i]:
            train[i-1], train[i] = train[i], train[i-1]
            swaps += 1
            i -= 1
    print('Optimal train swapping takes %d swaps.' % swaps)
