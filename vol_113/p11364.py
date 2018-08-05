
t = int(input())
assert 1 <= t <= 100

#def median(arr):
#    arr.sort()
#    if len(arr) % 2 != 0: return arr[len(arr)//2]
#    else: return (arr[len(arr)//2-1]+arr[len(arr)//2])//2

for z in range(t):
    n = int(input())
    assert 1 <= n <= 20
    stores = list(map(int,input().split()))
    assert len(stores) == n
    # carrying everything around means walking across the range twice
    print(2*(max(stores)-min(stores)))
