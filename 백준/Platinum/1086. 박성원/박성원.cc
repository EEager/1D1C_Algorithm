#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#define all(v) (v).begin(), (v).end()
#define press(v) (v).erase(unique(all(v)), (v).end())
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
const int MAX = 15;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int N, K, mod[MAX], p[51];
ll d[1 << MAX][100];
vector<string> v;
ll gcd(ll a, ll b) {
	ll r = a % b;
	if (!r)
		return b;
	return gcd(b, r);
}
ll fac(int n) {
	ll ret = 1;
	for (int i = 1; i <= n; i++) {
		ret *= i;
	}
	return ret;
}
int solve(string s) {
	ll ret = 0;
	for (int i = 0; i < s.length(); i++) {
		ret = (ret * 10 + (s[i] - '0')) % K;
	}
	return ret;
}
ll dp(int flag, int num) {
	if (flag == (1 << N) - 1)
		return num ? 0 : 1;
	ll& ret = d[flag][num];
	if (ret != -1)
		return ret;
	ret = 0;
	for (int i = 0; i < N; i++) {
		if (!(flag & (1 << i)))
			ret += dp(flag | (1 << i), (num * p[v[i].length()] + mod[i]) % K);
	}
	return ret;
}
int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> N;
	v.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i];
	}
	cin >> K;
	p[0] = 1 % K;
	for (int i = 1; i <= 50; i++) {
		p[i] = p[i - 1] * 10 % K;
	}
	for (int i = 0; i < N; i++) {
		mod[i] = solve(v[i]);
	}
	memset(d, -1, sizeof(d));
	ll ans1 = dp(0, 0);
	if (!ans1) {
		cout << "0/1" << "\n";
		return 0;
	}
	ll ans2 = fac(N);
	ll num = gcd(ans1, ans2);
	ans1 /= num;
	ans2 /= num;
	cout << ans1 << "/" << ans2 << "\n";
}