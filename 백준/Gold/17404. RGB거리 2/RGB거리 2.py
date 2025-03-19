INF = int(1e9)  # 무한대 값 설정

N = int(input())
cost = []

for _ in range(N):
    cost.append(list(map(int, input().split())))

result = INF

for first_color in range(3):
    dp = [[INF] * 3 for _ in range(N)] 

    dp[0][first_color] = cost[0][first_color]

    for i in range(1, N):
        dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0]
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + cost[i][1]
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2]

    for last_color in range(3):
        if last_color != first_color:
            result = min(result, dp[N - 1][last_color])

print(result)
