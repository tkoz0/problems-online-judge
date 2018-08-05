import sys

def colas(N,b):
    drank = 0
    full, empty = N, b
    while full != 0:
        drank += full
        empty += full
        full, empty = divmod(empty,3)
    if empty < b: return -1 # not enough to return borrowed
    else: return drank

for line in sys.stdin:
    N = int(line)
    # borrow 0 or 1 or 2 bottles
    # borrowing 3 would mean ability to convert them into 1 cola but only have
    # 1 bottle to return
    # youll end with 0 or 1 or 2 if you try to get as many as possible
    print(max(colas(N,0),colas(N,1),colas(N,2)))
