
index = []
while True:
    s = input()
    if s == '#': break
    index.append(s)

# build a trie data structure from the dictionary
class trie_node:
    def __init__(self):
        # characters and the children nodes they map to, ordered by input order
        self.arr = []
        self.children = []

trie = trie_node()

# insertion, given some base string, the next char must either be equal to the
# last one encountered, or new, otherwise we would be going backwards in the
# sorted order known for the current character index (given the root to parent
# path to get to current position)
# ordering is only guaranteed for the current base string, it is still possible
# for an input to have no valid sorting, ex: ZX, ZY, XY, XZ
# the trie is ZX root with children XY and YZ
# the directed graph generated has a cycle: Z-->X-->Y   (-->Z)
def trie_insert(root,w):
    for c in w:
        i = -1

        for j,ch in enumerate(root.arr): # find c in children
            if ch == c: i = j; break

        if i == -1: # must insert new trie node, doesnt have needed child
            root.arr.append(c)
            root.children.append(trie_node())
            root = root.children[-1] # proceed to appropriate child

        # not validly sorted, root.arr gives order found for the base string
        # from trie root to parent of current so this would be going backwards
        elif i != len(root.arr)-1: return False

        else: root = root.children[i] # proceed to appropriate child
    return True

for word in index: # insert in dictionary order
    assert trie_insert(trie,word)

# the trie allows finding a directed graph to order the letters
# build such a graph, if it has no cycles then a topological sorting exists
# find the topological sorting and print it

graph_in = dict() # contains incoming edges for kahn's algorithm
graph_out = dict()
nodes = [trie] # find nodes in trie
i = 0
while i < len(nodes): # collect all the nodes in the trie
    nodes += nodes[i].children
    i += 1
for node in nodes: # build the graph
    for i,c1 in enumerate(node.arr):
        # make sure every letter appears in keys for both graph dicts
        if not (c1 in graph_out): graph_out[c1] = set()
        if not (c1 in graph_in): graph_in[c1] = set()
        for j in range(i+1,len(node.arr)):
            if not (node.arr[j] in graph_in): graph_in[node.arr[j]] = set()
            graph_in[node.arr[j]].add(c1) # incoming edge from c1
            graph_out[c1].add(node.arr[j]) # outgoing edge from c1

#print(graph_in)
#print(graph_out)

# find a topological sorting
queue = [c for c in sorted(graph_in.keys()) if len(graph_in[c]) == 0]
top_sort = []
while len(queue):
    node = queue.pop(0)
    top_sort.append(node)
    for out in sorted(graph_out[node]): # node --> out (edge)
        graph_in[out].remove(node)
        graph_out[node].remove(out)
        # if no more incoming edges push to queue
        if len(graph_in[out]) == 0: queue.append(out)
# has a topological sorting if all nodes were visited
assert len(top_sort) == len(graph_in.keys())
print(''.join(top_sort))
