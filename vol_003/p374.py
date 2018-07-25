import sys

for line in sys.stdin:
    if line == '\n': continue
    B = int(line[:-1])
    P = int(sys.stdin.readline()[:-1])
    M = int(sys.stdin.readline()[:-1])
    # compute B**P % M (efficiently)
    print(pow(B,P,M))
#    R = 1
#    while P != 0: # modular exponentiation by squaring
#        if P % 2 == 1: R = (R*B) % M
#        P //= 2
#        B = (B*B) % M
#    print(R)
