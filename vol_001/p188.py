import sys
import random

def hash(word):
    m = 1 # base 32 multiplier
    h = 0 # hash
    for c in word[::-1]:
        h += (1+ord(c)-ord('a'))*m
        m <<= 5
    return h

def find_collision(W,C):
    n = len(W)
    new_C = 0
    for i in range(n):
        for j in range(n):
            if i != j and ((C//W[i])%n) == ((C//W[j])%n): # collision
                #new_C = max(new_C,min((C//W[i]+1)*W[i],(C//W[j]+1)*W[j]))
                return min((C//W[i]+1)*W[i],(C//W[j]+1)*W[j])
    return 0#new_C # 0 if no collision

def find_C(W): # W is integer list
    C = 1
    while True: # loop until found
        new_C = find_collision(W,C)
        if new_C == 0: break # none
        else: C = new_C
    return C

for line in sys.stdin:
    words = line.split()
    W = [hash(word) for word in words]
    print(line,end='')
    print(find_C(W))
    print()
