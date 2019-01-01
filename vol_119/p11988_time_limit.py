# this code is incorrect, assumes the whole input file is a single test case
# the problem actually has 1 test case per line

import sys

typed = sys.stdin.read()

# '[' = home
# ']' = end

# use a doubly linked list of strings to avoid reconcatenation of long lengths

class node:
    def __init__(self,value):
        self.value = value
        self.left = None
        self.right = None

head = None # represent the current list
tail = None

def insert(at_end,value):
    global head,tail
    if value == '': return # skip empty strings
    if not head:
        assert not tail
        head = tail = node(value)
    else:
        if at_end:
            tail.right = node(value)
            tail.right.left = tail
            tail = tail.right
        else:
            head.left = node(value)
            head.left.right = head
            head = head.left

# process text

ins_end = True # insert at end
i = 0 # index in typed
while True:
    j = i
    # find next [] char
    while j < len(typed) and typed[j] != '[' and typed[j] != ']': j += 1
    insert(ins_end,typed[i:j])
    if j == len(typed): break # reached end
    ins_end = (typed[j] == ']')
    i = j+1

# iterate over list and output strings

while head:
    print(head.value,end='')
    head = head.right
