import sys

longest = 0
sentences = []
for line in sys.stdin:
    sentences.append(line[:-1])
    longest = max(longest,len(sentences[-1]))
sentences = sentences[::-1]
for i in range(len(sentences)): sentences[i] += ' '*(longest-len(sentences[i]))
for r in range(longest):
    print(''.join(sentences[z][r] for z in range(len(sentences))))
