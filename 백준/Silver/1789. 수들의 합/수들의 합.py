# 서로 다른 N개의 자연수의 합이 S 일때, 자연수 N의 최대값
# 1부터합계를 구하고 S를 넘는다면, 마지막 숫자에 나머지를 더하면된다.
s = int(input())
sum = 0
cur = 1
while True:
    sum += cur
    if sum>s:
        break
    cur += 1
print(cur-1)
    