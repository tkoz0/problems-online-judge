
digits = set(str(d) for d in range(10)) # index i = whether digit was used
solutions = list([] for i in range(80)) # hard coded max
num = [] # digits in numerator

def find_solutions(selected,N):
    global digits, solutions, num
    if selected == 5:
        assert len(digits) == 5
        # denomenator = (numerator) / N
        numerator = int(''.join(num))
        denomenator, rem = divmod(numerator,N)
        if rem == 0 and sorted('%05d'%denomenator) == sorted(digits):
            solutions[N].append('%05d / %05d = %d'%(numerator,denomenator,N))
    else:
        for d in list(digits):
            digits.remove(d)
            num.append(d)
            find_solutions(selected+1,N);
            num.pop() # backtrack
            digits.add(d)

# generate all data
for N in range(2,79+1): find_solutions(0,N)
solutions = list(sorted(l) for l in solutions)

first = True
while True:
    N = int(input())
    if N == 0: break
    assert 2 <= N <= 79
    if not first: print() # blank line separator
    if len(solutions[N]) == 0: print('There are no solutions for %d.'%N)
    else:
        for s in solutions[N]: print(s)
    first = False
