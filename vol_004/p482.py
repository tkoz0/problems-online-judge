
cases = int(input())

for case in range(cases):
    input()
    ints = list(map(int,input().split()))
    floats = input().split()
    assert len(ints) == len(floats)
    array = [(ints[i],floats[i]) for i in range(len(ints))]
    array.sort(key=lambda x:x[0])
    if case != 0: print()
    for item in array: print(item[1])
