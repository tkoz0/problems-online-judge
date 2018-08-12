
while True:
    n = int(input())
    if n == 0: break
    assert n <= 1000
    cents = 0
    students = []
    for z in range(n):
        amount = round(float(input())*100.0)
        cents += amount
        students.append(amount)
    students.sort()
    # visualize the solution distribution as a line at pers and pers+1
    # compute the below which must be filled by the area above
    #            |----------------------- pers+1
    #            |
    # pers ------|
    pers = cents // n # per student (smaller amount)
    extra = cents % n
    exchangelo = 0
    exchangehi = 0
    for i,s in enumerate(students):
        if i < n - extra: # use smaller amount (pers)
            if s < pers: exchangelo += pers - s
            else: exchangehi += s - pers
        else: # use larger amount
            if s < pers+1: exchangelo += pers+1 - s
            else: exchangehi += s - (pers+1)
    assert exchangelo == exchangehi
    print('$%d.%02d'%divmod(exchangelo,100))
