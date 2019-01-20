
def gcd(a,b): # euclid gcd
    if a<b: a,b = b,a
    while b != 0: a,b = b,a%b
    return a

while True:
    nums = list(map(int,input().split()))
    assert len(nums) > 0 and nums[-1] == 0
    nums.pop() # exclude termination char
    if len(nums) < 2: break

    # let input be a_1, a_2, ..., a_n with n >= 2
    # let differences be d_1=a_1-a_2, d_2=a_2-a_3, ..., d_{n-1}=a_{n-1}-a_n
    # if a_1 = a_2 = ... = a_n (mod d) then
    # for any i,j we have a_i-a_j is divisible by d
    # suppose d divides all differences: d | d_1,d_2,...
    # then a_i-a_j=d_i+d_{i+1}+...+d_{j-1}
    # d divides any linear combination of all d_i values so it divides a_i-a_j

    d = abs(nums[0]-nums[1]) # gcd of first difference
    for i in range(2,len(nums)): # compute gcd of all differences
        d = gcd(d,abs(nums[i-1]-nums[i]))
    print(d)
