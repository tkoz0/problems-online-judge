import sys

for line in sys.stdin:
    k = int(line)
    # 1/x must be < 1/k so x minimum is k+1
    # if x > 2k, then y < 2k so solution may be repeated
    pairs = []
    for x in range(k+1,1+2*k):
        # 1/y = (x-k)/kx
        if k*x % (x-k) == 0: # divisible to 1 on numerator
            pairs.append((k*x//(x-k),x))
    print(len(pairs))
    for x,y in pairs: print('1/%d = 1/%d + 1/%d'%(k,x,y))
