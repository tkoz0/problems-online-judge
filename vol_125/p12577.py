
case = 0
while True:
    case += 1
    s = input()
    if s == '*': break
    if s == 'Hajj': print('Case %d: Hajj-e-Akbar' % case)
    else:
        assert s == 'Umrah'
        print('Case %d: Hajj-e-Asghar' % case)
