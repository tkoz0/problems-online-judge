
T = int(input())
assert T <= 1000

for case in range(T):
    N, K, P = map(int,input().split())
    assert 2 <= N <= 23 # N players in circle 1...N
    assert 1 <= K <= N # player K starts the practice
    assert 1 <= P <= 200 # number of passes
    # convert to 0..N-1 order, use modulus, then back to 1..N order
    print('Case %d: %d'%(case+1,1+((K-1+P)%N)))
