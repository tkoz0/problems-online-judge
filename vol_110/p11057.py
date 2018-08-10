
while True:
    try: line = input()
    except EOFError: break
    if line == '': continue # skip blank line
    N = int(line)
    assert 2 <= N <= 10000
    books = list(map(int,input().split()))
    M = int(input())
    if M % 2 == 0: # try 2 books with same cost
        count = 0
        for b in books:
            if b == M//2: count += 1
        if count >= 2:
            print('Peter should buy books whose prices are %d and %d.\n'
                  %(M//2,M//2))
            continue
    books = set(books)
    a, b = -1, M+1 # cost of 2 books
    for book in books: # minimize difference between 2 books
        other = M-book
        if (other in books) and (abs(other-book) < abs(a-b)):
            a, b = book, other
    print('Peter should buy books whose prices are %d and %d.\n'
          %(min(a,b),max(a,b)))
