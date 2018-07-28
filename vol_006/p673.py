
n = int(input())
for z in range(n):
    s = input()
    stack = []
    for c in s:
        if c == '(' or c == '[': stack.append(c)
        elif c == ')' or c == ']':
            # close nonexistint open bracket
            if len(stack) == 0: stack.append(c); break
            ch = stack.pop() # must close matching bracket
            if (ch == '(' and c != ')') or (ch == '[' and c != ']'):
                stack.append(c); break
    # success if stack is empty
    print('No' if len(stack) else 'Yes')
