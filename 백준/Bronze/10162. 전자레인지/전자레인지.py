# 300, 60, 10 으로 t를 만드는 최소개수
# a,b,c
ans = [0] * 3
times = [300,60,10]
t = int(input())
for idx, time in enumerate(times):
    while True:
        if t-time>=0:
            ans[idx]+=1
            t-=time
        else: break
if t>0:
    print(-1)
else:
    print(f"{ans[0]} {ans[1]} {ans[2]}")

