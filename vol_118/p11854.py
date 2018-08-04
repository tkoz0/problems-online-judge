
while True:
    nums = list(map(int,input().split()))
    assert len(nums) == 3
    nums.sort()
    if nums == [0,0,0]: break
    print('right' if nums[0]**2 + nums[1]**2 == nums[2]**2 else 'wrong')
