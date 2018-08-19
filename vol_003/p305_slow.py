
class node:
    def __init__(self,z):
        self.l = None
        self.r = None
        self.n = z

def make_list(k):
    assert k > 0
    head = node(1)
    tail = head
    for z in range(2,1+2*k):
        tail.r = node(z)
        tail.r.l = tail
        tail = tail.r
    head.l = tail # link cyclically
    tail.r = head
    return head

bestm = [0]*14

while True:
    k = int(input())
    if k == 0: break
    assert 0 < k < 14
    if bestm[k] != 0: print(bestm[k]) # previously computed
    else:
        # people 1...k are good, people k+1...2k are bad
        m = k # k+1 is smallest possible solution
        while True:
            m += 1
            ptr = make_list(k)
            assert ptr.n == 1
            bad_selected = 0 # must reach k before a good person is picked
            while bad_selected < k:
                for z in range(m-1): ptr = ptr.r # advance
                kill = ptr
                if kill.n <= k: break # selected good person
                bad_selected += 1
                ptr = ptr.r
                kill.l.r = kill.r
                kill.r.l = kill.l
            if bad_selected == k: break # all bad gone before any good
        print(m)
        bestm[k] = m
