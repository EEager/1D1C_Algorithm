t = int(input())
for _ in range(t):
    inputs = int(input())
    max = 0
    ans = ""
    for _ in range(inputs):
        s, a = input().split()
        a = int(a)
        if a > max:
            max = a
            ans = s
    print(ans)