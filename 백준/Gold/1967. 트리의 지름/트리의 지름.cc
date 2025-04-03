#include <vector>
#include <queue>
#include <iostream>
using namespace std;
vector<pair<int, int>> v[10001];
int n;

int bfs(int node, int step) {
	int dis[10001] = { 0, };
	queue<int> q;

	q.push(node);
	dis[node] = 0;
	while (!q.empty())
	{
		int tmp = q.front(); q.pop();
		for (auto y : v[tmp])
		{
			/* 그래프 하나씩 꺼내면서 확인 */
			/* y.first == node : 노드로 돌아가는것 방지. */
			if (y.first == node || dis[y.first] !=0)
				continue;
			dis[y.first] = dis[tmp] + y.second;
			q.push(y.first);
		}
	}
	int max = 0, last = 0;
	for (int i = 1; i <= n; i++) {
		if (max < dis[i]) {
			max = dis[i];
			last = i;
		}
	}
	return step == 1 ? last : max;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}

	int next = bfs(1,1);
	cout << bfs(next, 2) << endl;
}