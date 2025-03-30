h, m, s = list(map(int, input().split()))
cts = int(input())

h += (cts//60)//60
m += (cts//60)%60 
s += cts%60 

if s >= 60:
    m += 1
    s %= 60

if m >= 60:
    h += 1
    m %= 60
    
if h >= 24:
    h %= 24

print(h, m, s)