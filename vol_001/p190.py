import sys
from math import sqrt,pi

def sign(a): return '-' if a < 0.0 else '+'

for line in sys.stdin:
    x1, y1, x2, y2, x3, y3 = map(float,line.split())
    # find midpoint of p1,p2 then compute perpendicular line
    # every point on this line is equidistant from both p1 and p2
    # compute similar line for p2,p3, their intersection is circle center

    # compute midpoints
    m1x, m1y = (x1+x2)/2.0, (y1+y2)/2.0
    m2x, m2y = (x2+x3)/2.0, (y2+y3)/2.0

    # perpendicular vectors (delta x, delta y) --> (-delta y, delta x)
    v1x, v1y = y1-y2, x2-x1
    v2x, v2y = y2-y3, x3-x2

    # now must find c1,c2 such that m1+c1*v1 = m2+c2*v2
    # equations become c1*v1x - c2*v2x = m2x - m1x
    #                  c1*v1y - c2*v2y = m2y - m1y
    # matrix equation is
    # [ v1x  -v2x ] [ c1 ] = [ m2x-m1x ]
    # [ v1y  -v2y ] [ c2 ] = [ m2y-m1y ]
    # so we must solve for
    # [ c1 ] = [ v1x  -v2x ] -1 [ m2x-m1x ]
    # [ c2 ] = [ v1y  -v2y ]    [ m2y-m1y ]

    # represent original matrices
    m11, m12, m21, m22 = v1x, -v2x, v1y, -v2y
    det = (v1x)*(-v2y) - (-v2x)*(v1y)
    assert abs(det) > 2**(-32) # should have nonzero determinant
    b1, b2 = m2x-m1x, m2y-m1y

    # compute inverse
    mi11, mi12, mi21, mi22 = (1.0/det)*m22, (-1.0/det)*m12, \
                             (-1.0/det)*m21, (1.0/det)*m11
    c1 = mi11*b1 + mi12*b2
    c2 = mi21*b1 + mi22*b2

    # check intersection
    center1x, center1y = m1x+c1*v1x, m1y+c1*v1y
    center2x, center2y = m2x+c2*v2x, m2y+c2*v2y
    assert abs(center1x-center2x) < 2**(-32)
    assert abs(center1y-center2y) < 2**(-32)
    cx, cy = (center1x+center2x)/2.0, (center1y+center2y)/2.0

    # compute radius with each point
    r1 = sqrt((x1-cx)**2 + (y1-cy)**2)
    r2 = sqrt((x2-cx)**2 + (y2-cy)**2)
    r3 = sqrt((x3-cx)**2 + (y3-cy)**2)
    assert abs(r1-r2) < 2**(-32)
    assert abs(r2-r3) < 2**(-32)

    # final computation
    radius = (r1+r2+r3)/3.0
    circumference = 2.0*pi*radius
#    print('%.2f'%circumference)

    # center is (cx,cy) --> h = cx, k = cy
    # radius is radius --> r = radius
    h, k, r = cx, cy, radius
    # expand (x-h)^2+(y-k)^2=r^2
    # x^2-2hx+h^2+y^2-2ky+k^2=r^2
    # x^2+y^2 - 2hx - 2ky + (h^2+k^2-r^2) = 0
    c, d = -2.0*h, -2.0*k
    e = h*h + k*k - r*r
    print('(x %s %.3f)^2 + (y %s %.3f)^2 = %.3f^2'
            % (sign(-h),abs(h),sign(-k),abs(k),r))
    print('x^2 + y^2 %s %.3fx %s %.3fy %s %.3f = 0'
            % (sign(c),abs(c),sign(d),abs(d),sign(e),abs(e)))
    print()

