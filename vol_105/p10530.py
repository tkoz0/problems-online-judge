
while True:
    try: n, result = int(input()), input()
    except EOFError: break
    ns = [n]
    results = [result]
    while results[-1] != 'right on':
        n, result = int(input()), input()
        ns.append(n)
        results.append(result)
    lo, hi = 1, 10
    consistent = True
    for i in range(len(ns)):
        if results[i] == 'right on': # at end
            if not (lo <= ns[i] <= hi): consistent = False
        elif results[i] == 'too low':
            lo = max(lo,ns[i]+1)
            if lo > hi: consistent = False; break
        else:
            assert results[i] == 'too high'
            hi = min(hi,ns[i]-1)
            if lo > hi: consistent = False; break
    print('Stan may be honest' if consistent else 'Stan is dishonest')
