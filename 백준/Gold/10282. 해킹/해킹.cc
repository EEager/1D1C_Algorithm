#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int INF = 1e9;
vector<pii> g[10001];

void dijkstra(int start, int n) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [time, node] = pq.top();
        pq.pop();

        if (time > dist[node]) continue;

        for (auto &[nextNode, nextTime] : g[node]) {
            if (dist[nextNode] > time + nextTime) {
                dist[nextNode] = time + nextTime;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    int infected = 0, maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] != INF) {
            infected++;
            maxTime = max(maxTime, dist[i]);
        }
    }
    cout << infected << " " << maxTime << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, d, c;
        cin >> n >> d >> c;
        for (int i = 0; i <= n; i++) g[i].clear();

        for (int i = 0; i < d; i++) {
            int a, b, s;
            cin >> a >> b >> s;
            g[b].push_back({a, s});
        }

        dijkstra(c, n);
    }
    return 0;
}