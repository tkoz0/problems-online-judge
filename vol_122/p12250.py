
lang = {
    'HELLO': 'ENGLISH',
    'HOLA': 'SPANISH',
    'HALLO': 'GERMAN',
    'BONJOUR': 'FRENCH',
    'CIAO': 'ITALIAN',
    'ZDRAVSTVUJTE': 'RUSSIAN'}

case = 0
while True:
    case += 1
    S = input()
    if S == '#': break
    try: print('Case %d: %s' % (case,lang[S]))
    except KeyError: print('Case %d: UNKNOWN' % case)
