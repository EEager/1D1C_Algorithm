// 처음엔 reduction + trees[idx].cost가 큰 좌표만 선택제거함 => 반례가 있음 => 보니깐 완탐을해함
// 백트래킹으로 완탐해봄 => 역시나 시간초과 => state 비트마스킹 방법 + memo => 시간초과 => chatGPT 도와줘
// 가지치기 방법으로 현지 state에서 더진행해도 답이 없는 경우, 해당 분기를 버리는 방법이 있대.
// + 완탐 후보군 설정 : 
//  1)경계선에 있는 애들 
//  2)경계선안에 있는애중cost가장큰애 
//  3)1)2)를 reduction + trees[idx].cost으로 정렬 (휴리스틱하게 정렬)

#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int x, y, cost;
};

int N;
vector<Tree> trees;
int bestGlobal = INT_MAX;
const int INF = 1e9;

// 전역 memo: 각 상태(state, 비트마스크)에서의 최소 제거 횟수
unordered_map<unsigned long long, int> dp;

// popcount: state에서 1의 개수 (제거된 나무 수)
int popcount(unsigned long long state) {
    int count = 0;
    while (state) {
        count += (int)(state & 1ULL);
        state >>= 1;
    }
    return count;
}

// state에 대해, 제거된 나무들의 목재 합을 계산 (O(N))
int sumWood(unsigned long long state) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        if (state & (1ULL << i))
            sum += trees[i].cost;
    }
    return sum;
}

// state에 대해, 남아있는(제거되지 않은) 나무들의 좌표를 이용해 울타리 둘레를 계산 (O(N))
int computeBoundary(unsigned long long state) {
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    bool any = false;
    for (int i = 0; i < N; i++) {
        if (!(state & (1ULL << i))) { // 아직 제거되지 않은 나무
            any = true;
            minX = min(minX, trees[i].x);
            maxX = max(maxX, trees[i].x);
            minY = min(minY, trees[i].y);
            maxY = max(maxY, trees[i].y);
        }
    }
    if (!any) return 0; // 모두 제거됐다면 둘레 0
    return 2 * ((maxX - minX) + (maxY - minY));
}

// DFS: state는 현재까지 제거한 나무들의 집합 (비트마스크)
// 반환값은 state로부터 조건(목재합 >= 남은 나무들 울타리 둘레)을 만족하는 데 필요한 최소 제거 횟수 (이미 제거한 수도 포함)
int DFS(unsigned long long state) {
    // memoization
    if (dp.find(state) != dp.end()) return dp[state];

    int removedCount = popcount(state);
    int currentWood = sumWood(state);
    int boundary = computeBoundary(state);

    // 조건: 제거한 목재합이 울타리 둘레보다 크거나 같으면 이 상태부터는 조건을 만족.
    if (currentWood >= boundary) {
        dp[state] = removedCount;
        bestGlobal = min(bestGlobal, removedCount);
        return removedCount;
    }
    // 가지치기: 이미 너무 많이 제거했다면 종료.
    if (removedCount >= bestGlobal) return INF;

    // 현재 상태에서 남아있는 나무들의 경계 좌표 구하기
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (int i = 0; i < N; i++) {
        if (!(state & (1ULL << i))) {
            minX = min(minX, trees[i].x);
            maxX = max(maxX, trees[i].x);
            minY = min(minY, trees[i].y);
            maxY = max(maxY, trees[i].y);
        }
    }

    // 후보 선택: 남아있는 나무 중
    // (1) 경계에 있는 나무들 (즉, x==minX, x==maxX, y==minY, y==maxY)
    // (2) 내부에 있는 나무 중 cost가 가장 큰 나무 (center candidate)
    vector<int> candidates;
    for (int i = 0; i < N; i++) {
        if (!(state & (1ULL << i))) { // 아직 제거되지 않은 나무
            if (trees[i].x == minX || trees[i].x == maxX || trees[i].y == minY || trees[i].y == maxY) {
                candidates.push_back(i);
            }
        }
    }
    int centerCandidate = -1;
    int bestCost = -1;
    for (int i = 0; i < N; i++) {
        if (!(state & (1ULL << i))) {
            if (!(trees[i].x == minX || trees[i].x == maxX || trees[i].y == minY || trees[i].y == maxY)) {
                if (trees[i].cost > bestCost) {
                    bestCost = trees[i].cost;
                    centerCandidate = i;
                }
            }
        }
    }
    if (centerCandidate != -1)
        candidates.push_back(centerCandidate);

    // 휴리스틱 정렬: 각 후보에 대해
    // score = (현재 boundary - 후보 제거 후의 boundary) + tree.cost
    //// 높은 score일수록 “효과적인” 제거라고 가정
    //vector<pair<int, int>> candScore; // {score, tree index}
    //for (int idx : candidates) {
    //    unsigned long long newState = state | (1ULL << idx);
    //    int newBoundary = computeBoundary(newState);
    //    int reduction = boundary - newBoundary;
    //    int score = reduction + trees[idx].cost;
    //    candScore.push_back({ score, idx });
    //}
    //sort(candScore.begin(), candScore.end(), greater<pair<int, int>>());

    int bestAns = INF;
    // 후보에 대해 높은 휴리스틱 순으로 DFS 분기 진행
    for (auto& p : candidates) {
        int idx = p;
        int candidateAns = DFS(state | (1ULL << idx));
        bestAns = min(bestAns, candidateAns);
        // 만약 바로 최적의 분기가 나오면 더 이상 탐색하지 않음.
        if (bestAns == removedCount + 1) break;
    }

    dp[state] = bestAns;
    bestGlobal = min(bestGlobal, bestAns);
    return bestAns;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    trees.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> trees[i].x >> trees[i].y >> trees[i].cost;
    }

    dp.clear();
    bestGlobal = INT_MAX;
    unsigned long long initState = 0ULL; // 초기 상태: 아무것도 제거하지 않음
    int ans = DFS(initState);
    cout << ans << "\n";
    return 0;
}