
def rev(n): return int(str(n)[::-1])

N = int(input())
for z in range(N):
    a, b = map(int,input().split())
    print(rev(rev(a)+rev(b)))
