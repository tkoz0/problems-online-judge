
s = input()
assert s == '_'*11

while True:
    s = input()
    if s == '_'*11: break # end of tape
    assert s[0] == s[-1] == '|'
    s = s[1:-1]
    assert len(s) == 9
    value = 0
    for c in s:
        if c == 'o': value = value*2+1
        elif c == ' ': value = value*2
    print(chr(value),end='')
