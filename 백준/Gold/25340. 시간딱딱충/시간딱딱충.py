import sys 
input = sys.stdin.readline
#A:주기, B:유지, C:시작시간, D:건너는 시간, E:다음까지 
def f(s,A,B,C,D,E):
    n = len(A)
    curTime = s + E[0]
    for i in range(n):
        if (curTime<C[i]):
            curTime=C[i]

        if curTime+D[i] <= B[i] + C[i]:
            pass
        else:
            diff = curTime - (C[i] + B[i] - D[i])
            k = (diff + A[i] - 1) // A[i];  #이전 k값을 갖는다.
            newCycleStart = C[i] + k * A[i]
            if (curTime < newCycleStart):
                curTime = newCycleStart
            #curTime = curTime + (A[i] - (curTime%A[i]))
        curTime += D[i]
        if i<n-1:
            curTime += E[i+1]
    curTime += E[n]
    return curTime

def sol(T,A,B,C,D,E):
    l,r = 0, T 
    ret = -1
    while (l<=r):
        m = (l+r)//2
        if (f(m,A,B,C,D,E) >= T):
            r=m-1
            ret=m
        else:
            l=m+1
    print("YES" if ret!=-1 and f(ret,A,B,C,D,E) == T else "NO")

tc = int(input())
while tc>0:
    tc-=1
    n,t = map(int, input().split())
    A,B,C,D=[0]*n,[0]*n, [0]*n,[0]*n
    for i in range(n):
        A[i], B[i], C[i], D[i] = map(int, input().split())
    E=list(map(int,input().split()))

    sol(t,A,B,C,D,E)
    