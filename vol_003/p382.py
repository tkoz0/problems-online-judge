import sys

nums = []
for line in sys.stdin: nums += list(map(int,line.split()))
assert nums[-1] == 0
nums.pop() # 0 terminates list
assert 1 < len(nums) < 100

print('PERFECTION OUTPUT')
for n in nums:
    assert 1 <= n <= 60000
    # divisor sum for n=p^a*q^b*...=(p^(a+1)-1)/(p-1)*(q^(b+1)-1)/(q-1)*...
    z = n
    count = 0
    while z % 2 == 0: count += 1; z //= 2
    divs = (2**(count+1)-1)
    d = 3
    while d*d <= z:
        if z % d == 0:
            count = 1
            z //= d
            while z % d == 0: count += 1; z //= d
            divs *= (d**(count+1)-1)//(d-1)
        d += 2
    if z != 1: divs *= z+1
    if divs < 2*n: print('%5d  DEFICIENT' % n)
    elif divs > 2*n: print('%5d  ABUNDANT' % n)
    else: print('%5d  PERFECT' % n)
print('END OF OUTPUT')
