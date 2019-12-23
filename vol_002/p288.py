import sys

def splitline(line,split):
    line = line.split(split)
    return [line[0]] + sum([[split,z] for z in line[1:]],[])

for line in sys.stdin:
    line = line[:-1]
    line = splitline(line,'**')
    line = [[z] if z == '**' else splitline(z,'*') for z in line]
    line = sum(line,[])
    line = [[z] if z == '**' or z == '*' else splitline(z,'+') for z in line]
    line = sum(line,[])
    line = [[z] if z == '**' or z == '*' or z == '+' else splitline(z,'-')
            for z in line]
    line = sum(line,[])
    for z in line[1::2]: # operators
        assert z in ['**','*','+','-']
    for z in line[0::2]: # numbers
        assert z.isdigit()
    for i in range(0,len(line),2): # convert for python to do arithmetic
        line[i] = int(line[i])
#    print(line)
    # perform order of operations reducing at each step
    for i in range(len(line)-2,-1,-2):
        if line[i] == '**': # do exponents first (right to left)
            line[i-1:i+2] = [line[i-1]**line[i+1]]
#    print(line)
    i = 1 # multiplication (left to right)
    while i < len(line):
        if line[i] == '*':
            line[i-1:i+2] = [line[i-1]*line[i+1]]
        else: i += 2
#    print(line)
    i = 1 # addition and subtraction (left to right)
    while len(line) > 1:
        if line[1] == '+':
            line[0:3] = [line[0]+line[2]]
        else:
            assert line[i] == '-'
            line[0:3] = [line[0]-line[2]]
    assert len(line) == 1
    print(line[0])
