#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;

vector<int> tasks[MAX];
int whoWork[MAX];
bool v[MAX];

bool dfs(int employee) {
    if (v[employee])
        return false;
    v[employee] = true;
	for (auto n : tasks[employee]) {
		if (whoWork[n] == 0 || dfs(whoWork[n])) {
			whoWork[n] = employee;
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, M;
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++) {
		int c;
		cin >> c;
		for (int j = 0; j < c; j++) {
			int job;
			cin >> job;
			tasks[i].push_back(job);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
            for (int j=0;j<2;j++) {
                memset(v, 0, N+1);
		        if (dfs(i)) cnt++;
        }
    }

	cout << cnt;
}
