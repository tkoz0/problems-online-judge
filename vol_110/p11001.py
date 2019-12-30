
# nonzero length when Vtotal/n > V0 --> constrain n < Vtotal/V0
# with n constrainted, define for 1 <= n < Vtotal/V0:
# L(n) = 0.3n*sqrt(Vtotal/n-V0)
# --> L'(n) = 0 --> (solving) n = Vtotal / 2V0
# --> try both integers closest to this

from math import sqrt, floor, ceil

while True:
    Vtotal, V0 = map(float,input().split())
    if Vtotal == V0 == 0.0: break
    assert 0.0 < Vtotal <= 60000.0 and 0.0 < V0 <= 600.0
    def L(n): return 0.3*n*sqrt(Vtotal/n-V0)
    n = Vtotal / (2.0*V0)
    if abs(n-round(n)) < 2**-32: print(int(round(n))); continue # "integer"
    if floor(n) > 0.0: Lf = L(floor(n))
    else: Lf = 0.0
    try: Lc = L(ceil(n)) # if n too large, sqrt might have negative argument
    except Exception: print(int(floor(n))); continue
    #print('Lf,Lc = %f,%f'%(Lf,Lc))
    if abs(Lf-Lc) < 2**-32: print(0) # "equal"
    elif Lf > Lc: print(int(floor(n)))
    else: print(int(ceil(n)))
