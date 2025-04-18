//using namespace std;
//using ll = long long;
//using pll = pair<ll, ll>;
//
//int main() {
//    vector<pll> arr;
//    int N;
//    ll K;
//    cin >> N >> K;
//    for (int i = 0; i < N; i++) {
//        int a; ll b;
//        cin >> a >> b;
//        arr.push_back({ a, b });
//    }
//
//    sort(arr.begin(), arr.end(), [](auto& a, auto& b) { return a.second > b.second; });
//
//    ll maxSum = LLONG_MIN;
//    int l = 0, r = arr.size() - 1;
//    while (l < r) {
//        ll sum = arr[l].second + arr[r].second;
//
//        if (arr[l].first != arr[r].first && sum <= K) {
//            maxSum = max(maxSum, sum);
//            l++;  // 이동
//        }
//        else {
//            r--;  // 조건을 만족하지 않으면 r 이동
//        }
//    }
//
//    cout << (maxSum == LLONG_MIN ? "NO" : to_string(maxSum)) << endl;
//}

//=> 투포인터로 하면 답이 안나옴...

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int maxSumBinarySearch(vector<pll>& arr, ll K) {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) { return a.second < b.second; });

    ll maxSum = LLONG_MIN;
    for (int i = 0; i < arr.size(); i++) {
        ll target = K - arr[i].second;

        // 이분 탐색으로 target 이하의 최대값 찾기
        auto it = upper_bound(arr.begin(), arr.end(), make_pair(0LL, target),
            [](const pll& a, const pll& b) { return a.second < b.second; });

        if (it != arr.begin()) {
            --it;
            if (arr[i].first != it->first) {  // 서로 다른 a_i인지 확인
                maxSum = max(maxSum, arr[i].second + it->second);
            }
        }
    }
    return (maxSum == LLONG_MIN) ? -1 : maxSum;
}

int main() {
    int N;
    ll K;
    cin >> N >> K;
    vector<pll> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    ll result = maxSumBinarySearch(arr, K);
    cout << (result == -1 ? "NO" : to_string(result)) << endl;
}