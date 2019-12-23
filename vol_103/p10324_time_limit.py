
case = 0
while True:
    case += 1
    try: s01 = input()
    except EOFError: break # end with either EOF or empty line
    if s01 == '': break
    n = int(input())
    print('Case %d:'%case)
    for q in range(n):
        i, j = map(int,input().split())
        if i > j: i, j = j, i
        same = True
        for k in range(i+1,j+1):
            if s01[k] != s01[i]: same = False; break
        print('Yes' if same else 'No')
