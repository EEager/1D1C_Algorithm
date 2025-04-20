#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;
typedef pair<int, int> pii;

vector<vector<pii>> graph;
vector<int> dijk(int start, int V) {
    vector<int> dist(V + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (cost > dist[node]) continue;

        for (auto& edge : graph[node]) {
            auto [next, weight] = edge;
            int nextCost = cost + weight;

            if (nextCost < dist[next]) {
                dist[next] = nextCost;
                pq.push({ nextCost, next });
            }
        }
    }
    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, V, E;
    cin >> N >> V >> E;

    graph.resize(V + 1);

    int A, B;
    cin >> A >> B;

    vector<int> homes(N);
    for (int i = 0; i < N; i++) {
        cin >> homes[i];
    }

    for (int i = 0; i < E; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        graph[a].push_back({ b, l });
        graph[b].push_back({ a, l });
    }

    vector<int> distFromA = dijk(A, V);
    vector<int> distFromB = dijk(B, V);

    int totalDistance = 0;
    for (int home : homes) {
        int dA = distFromA[home];
        int dB = distFromB[home];

        if (dA == INF || dB == INF) {
            totalDistance += -1;
        }
        else {
            totalDistance += dA + dB;
        }
    }

    cout << totalDistance << endl;
    return 0;
}