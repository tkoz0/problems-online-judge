
wordchars = '_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

# yield C tokens, "struct", "{", "}", ";", ",", types and names
def tokens(s):
    i = 0
    while i < len(s):
        if s[i] in ' \n\t':
            i += 1
        elif s[i] in '{},;':
            yield s[i]
            i += 1
        else:
            assert s[i] in wordchars
            token = ''
            while i < len(s) and s[i] in wordchars:
                token += s[i]
                i += 1
            yield token

# T1,..,T9 are types of size 1,..,9 bytes, T0 is a identifier

def read_struct(T,W,outer_structs=[],prev_ids=[]):
    pass

# tokens T, word size W
# outer_structs used to detect recursive structures
# prev_ids used to detect duplicate identifier
# return size of the type, name of type
def read_type(T,W,outer_structs=[],prev_ids=[]):
    type_ = next(T)
    if type_ in ['T1','T2','T3','T4','T5','T6','T7','T8','T9']:
        size = int(type_[1])
        id = next(T)
        assert next(T) == ';'
        return size,id
    elif type_ == 'struct':
        name = next(T)
        if name == '{':
            pass
        else:
            pass
    else:
        pass

N = int(input())
for _ in range(N):
    W = int(input())
    assert 0 < W < 100
    text = ''
    while True:
        line = input()
        if line == '$\n':
            break
        text += line
