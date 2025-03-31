t = int(input())
for _ in range(t):
    y, k = 0, 0
    for s in range(9):
        a,b = map(int, input().split())
        y, k = y + a, k + b
    if y==k:print("Draw")
    elif y>k:print("Yonsei")
    else:print("Korea")