
M = int(input())

for _ in range(M):
    N, K = map(int,input().split())
    assert 1 <= N <= 10000
    assert 2 <= K <= 100
    nums = list(map(int,input().split()))
    assert len(nums) == N
    mods = [False]*K # mod values that are possible
    mods[nums[0]%K] = True # 1st number
    for i in range(1,N): # update for each number
        mods2 = [False]*K # updated possible mod values
        for j,v in enumerate(mods):
            if v: # possible with all previous numbers
                # these 2 are possible considering new number
                mods2[(j-nums[i])%K] = True
                mods2[(j+nums[i])%K] = True
        mods = mods2
    print('Divisible' if mods[0] else 'Not divisible')

