import math

def gcd(a,b):
    if a < b: a,b = b,a
    while b != 0:
        a, b = b, a%b
    return a

while True:
    N = int(input())
    if N == 0: break
    nums = []
    for z in range(N): nums.append(int(input()))
    pairs = len(nums)*(len(nums)-1)//2
    coprime = 0
    for i in range(N):
        for j in range(i+1,N):
            if gcd(nums[i],nums[j]) == 1: coprime += 1
    if coprime == 0: print('No estimate for this data set.')
    else:
        ratio = coprime/pairs # r = 6/pi^2 --> pi = sqrt(6/r)
        print('%.6f'%(math.sqrt(6/ratio)))
