#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

long long countSubarraySum(vector<int>& arr, long long k) {
    unordered_map<long long, long long> prefixSum;
    long long sum = 0, count = 0;

    prefixSum[0] = 1; 

    for (int num : arr) {
        sum += num;

        if (prefixSum.count(sum - k)) {
            count += prefixSum[sum - k];  
        }

        prefixSum[sum]++;
    }

    return count;
}

int main() {
    long long n, k;
    cin >> n >> k;
    vector<int> arr(n);

    for (long long i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << countSubarraySum(arr, k) << endl;

    return 0;
}