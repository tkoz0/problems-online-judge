import sys

# map chars to their mirrors
mirror = {
    'A': 'A', 'B': '' , 'C': ''  , 'D': '' , 'E': '3', 'F': '' ,
    'G': '' , 'H': 'H', 'I': 'I' , 'J': 'L', 'K': '' , 'L': 'J',
    'M': 'M', 'N': '' , 'O': 'O0', 'P': '' , 'Q': '' , 'R': '' ,
    'S': '2', 'T': 'T', 'U': 'U' , 'V': 'V', 'W': 'W', 'X': 'X',
    'Y': 'Y', 'Z': '5', '0': '0O', '1': '1', '2': 'S', '3': 'E',
    '4': '' , '5': 'Z', '6': ''  , '7': '' , '8': '8', '9': '' }

for line in sys.stdin:
    line = line[:-1] # ignore \n
    pal = line == line[::-1]
    mir = True
    for i in range((len(line)+1)//2):
        if not (line[-(i+1)] in mirror[line[i]]): mir = False; break
    if (not pal) and (not mir): print(line,'-- is not a palindrome.')
    elif pal and (not mir): print(line,'-- is a regular palindrome.')
    elif (not pal) and mir: print(line,'-- is a mirrored string.')
    else: print(line,'-- is a mirrored palindrome.')
    print()
