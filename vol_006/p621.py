
n = int(input())

for z in range(n):
    e = input()
    if e == '1' or e == '4' or e == '78': print('+')
    elif e[-2:] == '35': print('-')
    elif e[0] == '9' and e[-1] == '4': print('*')
    elif e[:3] == '190': print('?')
    else: assert 0
