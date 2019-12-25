
cases = int(input())

def repeated_digits(n):
    count = [0]*10
    while n != 0:
        n,m = divmod(n,10)
        count[m] += 1
        if count[m] > 1: return True
    return False

taken = [False]*10 # digits taken in gen_s2

def gen_s2(num,limit):
    global taken
    if 0 < num <= limit: yield num
    if 10*num <= limit: # recursion
        high_digit = min(9,limit-10*num)
        low_digit = 1 if num == 0 else 0 # cannot start with 0
        for d in range(low_digit,1+high_digit):
            if taken[d]: continue
            taken[d] = True
            for z in gen_s2(10*num+d,limit): yield z
            taken[d] = False

for _ in range(cases):
    input()
    N = int(input())
    # s1/s2=N --> s1=N*s2 so we can try multiples of N and check s1
    # N*s2 < 9876543210 so we can limit s2 to 9876543210/N
    results = [] # store each s1
    s2nums = gen_s2(0,9876543210//N)
    for s2 in s2nums:
        s1 = N*s2
        if not repeated_digits(s1): results.append(s1)
    results.sort()
    if _ != 0: print()
    for s1 in results: print('%d / %d = %d'%(s1,s1//N,N))
