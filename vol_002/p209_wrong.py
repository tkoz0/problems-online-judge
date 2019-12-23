import sys
import math

# k(k-1)/2 < x <= k(k+1)/2
# --> k^2-2k+1 <= k^2-k < 2x <= k^2+k < k^2+2k+1
# --> k-1 < sqrt(2x) < k+1
def line_num(x): # line num k, floor(sqrt(2x)) is either k-1 or k
    k = int(math.sqrt(2*x))
    if k*(k-1)//2 < x <= k*(k+1)//2: return k
    else: return k+1 # we got k-1 so increment 1

def coord(x): # (line_num,position) where 1 <= position <= line_num
    k = line_num(x)
    return (k,x-k*(k-1)//2)

def is_triangle(a,b,c):
    a, b, c = sorted([a,b,c])
    pa, pb, pc = coord(a), coord(b), coord(c)
    # case 1, a is top point, b,c are on same line below
    line_dif = pb[0] - pa[0]
    # a and b have same on line coordinate, and b,c on same line
    if line_dif > 0 and pa[1] == pb[1] \
        and pb[0] == pc[0] \
        and line_dif == pc[1] - pb[1]: # b and c spaced apart correct distance
        return True;
    # case 2: a,b on same line, c is on a line below
    if pa[0] != pb[0]: return False
    spacing = pb[1] - pa[1]
    if spacing == pc[0] - pb[0] and pb[1] == pc[1]:
        return True # c is correct number of lines below, same line position
    return False # fails all cases

def is_parallelogram(a,b,c,d):
    a, b, c, d = sorted([a,b,c,d])
    pa, pb, pc, pd = coord(a), coord(b), coord(c), coord(d)
    if pa[0] == pb[0]: # case 1: top 2 are on same line
        # c and d must be on the same (lower) line
        # a,c must be on a valid grid line
        # the spacing between c,d must be the same as the spacing between a,b
        line_dif = pc[0] - pa[0]
        if line_dif != pb[1] - pa[1]:
            return False # ATTEMPT: REQUIRE SAME SIDE LENGTHS
        if pc[0] == pd[0] and (pa[1] == pc[1] or pc[1] == pa[1] + line_dif) \
            and pd[1]-pc[1] == pb[1]-pa[1]: return True
        else: return False
    else: # case 2: first 2 are on different lines
        if pb[1] == pa[1]: # one possible line for a,b
            lines_down = pd[0] - pb[0]
            if lines_down != pb[0] - pa[0]:
                return False # ATTEMPT: REQUIRE SAME SIDE LENGTHS
            if pd[1] - pb[1] == lines_down: # d and b on proper line
                return pc == (a+lines_down,pd[1])
            else: return False
        else:
            lines_down = pb[0] - pa[0]
            if pb[1] != pa[1] + lines_down: return False # not on proper line
            lines_down2 = pc[0] - pa[0]
            if lines_down != lines_down2:
                return False # ATTEMPT: REQUIRE SAME SIDE LENGTHS
            # a,c on proper line, can determine d position
            return pa[1] == pc[1] and pd == (pc[0]+lines_down,pb[1])

def is_hexagon(a,b,c,d,e,f):
    a, b, c, d, e, f = sorted([a,b,c,d,e,f])
    pa,pb,pc,pd,pe,pf = coord(a),coord(b),coord(c),coord(d),coord(e),coord(f)
    if pa[0] != pb[0]: return False # a,b need to be on same line
    side = pb[1] - pa[1] # side length of the hexagon
    # this enables determining the location of all the points on the hexagon
    return pc == (pa[0]+side,pa[1]) and \
            pd == (pb[0]+side,pb[1]+side) and \
            pe == (pc[0]+side,pc[1]+side) and \
            pf == (pd[0]+side,pd[1])

for line in sys.stdin:
    nums = list(map(int,line.split()))
    assert 1 <= min(nums) and max(nums) <= 32767 # all points in range
# below assertion failed in one test, removing fixed the runtime error
#    assert len(set(nums)) == len(nums) # all points unique
    nums_dedup = [] # keep same order in dedupe of nums
    for n in nums:
        if not (n in nums_dedup): nums_dedup.append(n)
    nums = nums_dedup
    if len(nums) == 3 and is_triangle(nums[0],nums[1],nums[2]):
        print(' '.join(str(x) for x in nums), 'are the vertices of a triangle')
    elif len(nums) == 4 and is_parallelogram(nums[0],nums[1],nums[2],nums[3]):
        print(' '.join(str(x) for x in nums),
              'are the vertices of a parallelogram')
    elif len(nums) == 6 and is_hexagon(nums[0],nums[1],nums[2],
                                       nums[3],nums[4],nums[5]):
        print(' '.join(str(x) for x in nums), 'are the vertices of a hexagon')
    else: print(' '.join(str(x) for x in nums),
                'are not the vertices of an acceptable figure')
