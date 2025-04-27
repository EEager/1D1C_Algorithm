#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll simulate(int s, int N, const vector<int>& A, const vector<int>& B,
            const vector<int>& C, const vector<int>& D, const vector<int>& E) {
    ll currentTime = s + E[0]; 
    for (int i = 0; i < N; i++) {
        if (currentTime < C[i])
            currentTime = C[i];
        
        if (currentTime <= C[i] + B[i] - D[i]) {
        } else {
            int diff = currentTime - (C[i] + B[i] - D[i]);
            int k = (diff + A[i] - 1) / A[i];  // ceiling division
            ll newCycleStart = C[i] + (ll)k * A[i];
            if (currentTime < newCycleStart)
                currentTime = newCycleStart;
        }
        currentTime += D[i];
   
        if (i < N - 1)
            currentTime += E[i + 1];
    }
   
    currentTime += E[N];
    return currentTime;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int TC; 
    cin >> TC;
    
    while(TC--){
        int N, T; 
        cin >> N >> T;

        vector<int> A(N), B(N), C(N), D(N);
        for (int i = 0; i < N; i++){
            cin >> A[i] >> B[i] >> C[i] >> D[i];
        }
       
        vector<int> E(N + 1);
        for (int i = 0; i <= N; i++){
            cin >> E[i];
        }
        
        int low = 0, high = T;
        int ans = -1;
        while(low <= high) {
            int mid = (low + high) / 2;
            ll arrival = simulate(mid, N, A, B, C, D, E);
            if(arrival >= T) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
   
        if(ans != -1 && simulate(ans, N, A, B, C, D, E) == T)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    
    return 0;
}