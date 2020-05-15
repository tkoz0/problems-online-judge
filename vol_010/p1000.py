
# pdf looks like theres 2 spaces between Configuration and Load
# use 1 space to avoid presentation error

while True:
    N = int(input())
    if N == 0: break
    P = [[0]*(N+1) for _ in range(N+1)] # P[i][j] passengers from city i to j
    for _ in range(N):
        line = list(map(int,input().split()))
        origin = line[0]
        k = line[1]
        assert len(line) == 2*k+2
        for i in range(2,len(line),2):
            P[origin][line[i]] = line[i+1]
    # configurations
    print('Configuration Load')
    data = [] # list of (load,conf_num) pairs
    while True:
        conf = int(input())
        if conf == 0: break
        arrive = list(map(int,input().split()))
        depart = list(map(int,input().split()))
        # make mappings for city number to position
        city2arrive = [0]*(N+1)
        city2depart = [0]*(N+1)
        for i,city in enumerate(arrive): city2arrive[city] = i
        for i,city in enumerate(depart): city2depart[city] = i
        load = 0
        for i in range(1,N+1):
            for j in range(1,N+1):
                dist = 1+abs(city2arrive[i]-city2depart[j])
                load += dist*P[i][j]
        data.append((load,conf))
    for load,conf in sorted(data): print('%5d         %d'%(conf,load))
