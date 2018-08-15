
T = int(input())

for z in range(T):
    ans = input()
    streak = 0
    score = 0
    for c in ans:
        if c == 'O': streak += 1
        else: score += streak*(streak+1)//2; streak = 0
    score += streak*(streak+1)//2
    print(score)
