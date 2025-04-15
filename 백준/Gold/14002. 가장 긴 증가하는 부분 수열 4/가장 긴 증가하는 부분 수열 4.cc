#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<int> dp(N, 1), prev(N, -1);
    int max_length = 0, last_index = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] < A[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_length) {
            max_length = dp[i];
            last_index = i;
        }
    }

    vector<int> LIS;
    while (last_index != -1) {
        LIS.push_back(A[last_index]);
        last_index = prev[last_index];
    }
    reverse(LIS.begin(), LIS.end());

    cout << max_length << endl;
    for (int num : LIS) {
        cout << num << " ";
    }

    return 0;
}