#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; 

int main() {
    int N;
    cin >> N;

    vector<vector<int>> cost(N, vector<int>(3)); 

    for (int i = 0; i < N; ++i) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    int result = INF;

    for (int first_color = 0; first_color < 3; ++first_color) {
        vector<vector<int>> dp(N, vector<int>(3, INF)); 

        dp[0][first_color] = cost[0][first_color]; //처음 색 고정

        for (int i = 1; i < N; ++i) {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + cost[i][1];
            dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2];
        }

        // 마지막 집의 색이 1번 집의 색과 같지 않은 경우만 고려
        for (int last_color = 0; last_color < 3; ++last_color) {
            if (last_color != first_color) {
                result = min(result, dp[N - 1][last_color]);
            }
        }
    }

    cout << result << endl;

    return 0;
}
