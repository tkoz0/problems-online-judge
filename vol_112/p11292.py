
while True:
    n, m = map(int,input().split())
    if n == m == 0: break
    assert 1 <= n <= 20000 # heads
    assert 1 <= m <= 20000 # knights
    heads = sorted(int(input()) for z in range(n))
    knights = sorted(int(input()) for z in range(m))
    # greedy algorithm, go through heads and knights in increasing order
    # pick smallest knight that can cut the next head needed
    selected = []
    for i,k in enumerate(knights):
        if n-len(selected) > m-i: break # not enough knights
        if len(selected) == n: break # enough knights
        # pick next knight if its big enough to cut next head
        if heads[len(selected)] <= k: selected.append(k)
    if len(selected) == n: print(sum(selected))
    else: print('Loowater is doomed!')
