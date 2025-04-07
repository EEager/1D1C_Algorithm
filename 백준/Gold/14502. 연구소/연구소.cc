#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 8;
int N, M;
int MAP[MAX][MAX], TMP[MAX][MAX];
vector<pii> virus, empty_spaces;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

void spreadVirus() {
    queue<pii> q;
    for (auto v : virus) q.push(v);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < N && ny < M && TMP[nx][ny] == 0) {
                TMP[nx][ny] = 2;
                q.push({ nx, ny });
            }
        }
    }
}

int getSafeZone() {
    int safe = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (TMP[i][j] == 0) safe++;
    return safe;
}

int solve() {
    int max_safe_zone = 0;
    vector<int> perm(empty_spaces.size(), 0);
	fill(perm.end() - 3, perm.end(), 1); // [0,0,0,...1,1,1]

    do {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                TMP[i][j] = MAP[i][j];

        for (int i = 0; i < empty_spaces.size(); i++)
            if (perm[i]) TMP[empty_spaces[i].first][empty_spaces[i].second] = 1;

        spreadVirus();
        max_safe_zone = max(max_safe_zone, getSafeZone());

    } while (next_permutation(perm.begin(), perm.end()));

    return max_safe_zone;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 0) empty_spaces.push_back({ i, j });
            if (MAP[i][j] == 2) virus.push_back({ i, j });
        }

    cout << solve();
}