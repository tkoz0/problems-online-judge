import sys

for line in sys.stdin:
    nums = list(map(int,line.split()))
    n = nums[0]
    nums = nums[1:]
    assert n <= 3000 and len(nums) == n
    difs = [False]*n
    jolly = True
    for i in range(1,n):
        dif = abs(nums[i]-nums[i-1])
        # invalid absolute difference or one that already occurred
        if dif == 0 or dif >= n or difs[dif]: jolly = False; break
        difs[dif] = True
    print('Jolly' if jolly else 'Not jolly')
