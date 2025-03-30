t = int(input())
ans = 0
for _ in range(t):
    a, b, c = map(int, input().split())
    if a == b == c:
        ans = max(ans, 10000 + a * 1000)
    elif len(set([a, b, c])) == 2:
        same = a if a == b or a == c else b
        ans = max(ans, 1000 + same * 100)
    else:
        ans = max(ans, max(a, b, c) * 100)

print(ans)