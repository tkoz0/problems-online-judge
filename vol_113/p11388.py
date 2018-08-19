
def gcd(x,y):
    if x < y: x,y = y,x
    while y != 0: x,y = y,x%y
    return x

# LCM(x,y) = x*y / GCD(x,y)
# use a=xG and b=yG, gcd(x,y)=1
# this is required for gcd(a,b)=G
# for LCM(a,b)=L we have LCM(a,b)=xyG sowe must factor L/G if it is integer
# pick some xy=L/G pair with x minimal (1)

T = int(input())
assert T <= 100

for z in range(T):
    G, L = map(int,input().split())
    if L % G != 0: print(-1)
    else:
        v = L//G
        # use x=1, y=v
        print(G,v*G)
