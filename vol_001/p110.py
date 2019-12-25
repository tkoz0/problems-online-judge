import sys

alphabet = 'abcdefgh'

class DAG:
    def __init__(self,n):
        assert 1 <= n <= 8
        self.n = n
        self.graph = dict()
        self.indeg = dict() # in degrees for each vertex
        for c in alphabet[:n]:
            self.graph[c] = []
            self.indeg[c] = 0
        self.topsort = [] # the order
        self.queue = list(alphabet[:n]) # all initially sources
    def add_edge(self,u,v): # make some queued vertex not a source anymore
        assert u != v
        assert v in self.queue # edge u,v will not exist since v is a source
        self.graph[u].append(v)
        self.indeg[v] = 1
        self.queue.remove(v) # no longer a source
    def try_topsort(self): # true if topsort finishes successfully
        if len(self.queue) == 0:
            assert len(self.topsort) == self.n
            return True
        while len(self.queue) == 1: # pick unique vertex, add to topsort
            u = self.queue.pop()
            self.topsort.append(u)
            for v in self.graph[u]: # remove outgoing edges
                self.indeg[v] -= 1 # add new sources to queue
                if self.indeg[v] == 0: self.queue.append(v)
            self.graph[u] = []
        if len(self.queue) > 1: return False # cannot pick unique next vertex
        else:
            assert len(self.topsort) == self.n
            return True
    def clone(self):
        dag = DAG(self.n)
        for c in alphabet[:self.n]:
            dag.graph[c] = self.graph[c][:]
            dag.indeg[c] = self.indeg[c]
        dag.topsort = self.topsort[:]
        dag.queue = self.queue[:]
        return dag

def write_logic(data,n,depth,dag):
    if dag.try_topsort(): # success
        data[n].append('  '*depth+'writeln(%s)'%(','.join(dag.topsort),))
    else: # connect 2 queued vertices
        assert len(dag.queue) > 1
        dag1 = dag.clone() # copies for split recursion
        dag2 = dag.clone()
        u,v = dag.queue[0],dag.queue[1]
        dag1.add_edge(u,v)
        dag2.add_edge(v,u)
        data[n].append('  '*depth+'if %s < %s then'%(u,v))
        write_logic(data,n,depth+1,dag1)
        data[n].append('  '*depth+'else')
        write_logic(data,n,depth+1,dag2)

def write_program(data,n):
    assert 1 <= n <= 8
    data[n].append('program sort(input,output);')
    data[n].append('var')
    data[n].append(','.join(list(alphabet[:n]))+' : integer;')
    data[n].append('begin')
    data[n].append('  readln(%s);'%(','.join(list(alphabet[:n])),))
    write_logic(data,n,1,DAG(n))
    data[n].append('end.')

data = [[] for _ in range(1+8)] # data[i] stores output for i letters to sort
for i in range(1,1+8):
    write_program(data,i)

M = int(input())

for case in range(M):
    input()
    n = int(input())
    assert 1 <= n <= 8
    if case != 0: print()
    for line in data[n]: print(line)
