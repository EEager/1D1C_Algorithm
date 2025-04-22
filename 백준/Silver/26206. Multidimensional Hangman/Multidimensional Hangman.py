import sys
from collections import defaultdict

N, C = map(int, sys.stdin.readline().split())
words = [sys.stdin.readline().strip() for _ in range(N)]
possible = [set() for _ in range(C)]
for word in words:
    for i, ch in enumerate(word):
        if ch != '*':
            possible[i].add(ch)

# 아 반례로 모든 단어가 *일수가잇구나..
for i in range(C):
    if not possible[i]:
        possible[i] = set("abcdefghijklmnopqrstuvwxyz")
candidate = defaultdict(int)
for word in words:
    lst = list(word)
    for i, ch in enumerate(word):
        if ch == '*':
            for p in possible[i]:
                lst[i] = p
                candidate["".join(lst)] += 1
            lst[i] = '*'
maxCount = max(candidate.values())
ans = min([w for w, cnt in candidate.items() if cnt == maxCount])
# ans = min(candidate, key=lambda x : (-candidate[x],x))
print(f"{ans} {maxCount}")