
while True:
    N = int(input())
    if N == 0: break
    assert N <= 1000
    orderings = []
    while True:
        orderings.append(list(map(int,input().split())))
        if len(orderings[-1]) == 1 and orderings[-1][0] == 0:
            orderings.pop()
            break
    queue = 1 # next train car on side A
    stack = [] # station
    for order in orderings:
        queue, stack = 1, [] # reset
        success = True
        for next_ in order:
            if len(stack) > 0 and stack[-1] == next_: stack.pop() # on stack
            else: # search queue for needed next train car
                if queue > next_: success = False; break # cant get required car
                while queue < next_: stack.append(queue); queue += 1
                queue += 1 # successfully found needed train car
        print('Yes' if success else 'No')
    print()
