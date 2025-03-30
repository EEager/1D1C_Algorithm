h, m = list(map(int, input().split()))
cook = int(input())

h += cook // 60
m += cook % 60

if m >= 60:
    h += 1
    m -= 60
    
if h >= 24:
    h -= 24

print(h, m)