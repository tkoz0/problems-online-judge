
while True:
    line = input()
    if line == '0': break
    # alternating digit sum must be divisible by 11
    altsum = 0
    for c in line[::2]: altsum += int(c)
    for c in line[1::2]: altsum -= int(c)
    print('%s is%s a multiple of 11.'%(line,'' if altsum % 11 == 0 else ' not'))
