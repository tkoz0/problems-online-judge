import sys

quoted = False
for line in sys.stdin:
    out = '' # conversion of current line based on quoting
    for c in line:
        if c == '"': # replace with proper quoting sequence for tex
            if quoted: out += "''"
            else: out += '``'
            quoted = not quoted
        else: out += c # other chars
    print(out,end='') # dont print \n twice
