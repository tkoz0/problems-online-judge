import os

url_base = 'https://uva.onlinejudge.org/external/'

#volumes = list(range(1,1+17)) + list(range(100,1+133))
volumes = [1]

for volume in volumes:
    os.system('mkdir %d'%volume)
    os.chdir('%d'%volume)
    for problem in range(100):
        url = url_base + '%d/%d%02d.pdf'%(volume,volume,problem)
        os.system('wget "%s"'%url)
    os.chdir('..')

