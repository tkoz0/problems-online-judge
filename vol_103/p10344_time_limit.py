
def search2(nums,current,goal): # pick a next number and operation
    if len(nums) == 0: return current == goal
    for i in range(len(nums)):
        a = nums[i]
        nums2 = nums[:i]+nums[i+1:]
        if search2(nums2,current+a,goal): return True # try 3 operations
        if search2(nums2,current-a,goal): return True
        if search2(nums2,current*a,goal): return True
    return False

def search(nums,goal):
    for i in range(len(nums)): # initiate searches with first number
        if search2(nums[:i]+nums[i+1:],nums[i],goal):
            return True
    return False

while True:
    nums = list(map(int,input().split()))
    if set(nums) == set([0]): break
    for n in nums: assert 1 <= n <= 50
    print('Possible' if search(nums,23) else 'Impossible')

