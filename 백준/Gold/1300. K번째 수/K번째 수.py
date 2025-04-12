# bk 인덱스를 찾기 위해서 
# 이 값보다 작은 숫자가 몇 개 있는지 찾아세자
def f(mid, N):
    count = 0
    for i in range(1, N + 1):
        count += min(mid // i, N) 
    return count

def bs(N, k):
    left, right = 1, N * N
    answer = 0

    while left <= right:
        mid = (left + right) // 2
        count = f(mid, N)

       # 6의 개수가 bk보다 크다 -> bk 인덱스는 6보다 작다.
        if count >= k:
            answer = mid  
            right = mid - 1  
        # 6의 개수가 bk보다 작다 -> bk 인덱스는 6보다 크다.
        else:
            left = mid + 1

    return answer

N = int(input())  
k = int(input()) 

print(bs(N, k))  