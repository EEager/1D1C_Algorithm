/*
삼분탐색 (ternary search) 사용
 최적화 문제의 특성—즉, 시간(t)에 따른 필요한 L의 값(혹은 그와 유사한 함수)이 
 유니모달(단 한 번의 최솟값 또는 최댓값을 갖는)하다는 점—때문에 매우 적합
*/
#include <bits/stdc++.h>
using namespace std;

int N;
// 각 쥐의 초기 위치 (px, py)와 속도 (vx, vy)
vector<tuple<double, double, double, double>> rats;

// 시간 t에서 쥐의 bounding box 크기를 구하는 함수
// 즉, 모든 쥐를 완벽히 (경계 제외) 포함하기 위해 필요한 최소 정사각형 변의 길이
double f(double t) {
    double minX = 1e9, maxX = -1e9;
    double minY = 1e9, maxY = -1e9;
    for (const auto& rat : rats) {
        double px, py, vx, vy;
        tie(px, py, vx, vy) = rat;
        double x = px + vx * t;
        double y = py + vy * t;
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
    }
    return max(maxX - minX, maxY - minY);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    rats.resize(N);
    for (int i = 0; i < N; i++) {
        double a, b, c, d;
        cin >> a >> b >> c >> d;
        rats[i] = { a, b, c, d };
    }

    // 시간 t의 범위를 0부터 3000초까지로 설정.
    double lowT = 0.0, highT = 3000.0;
    double precision = 1e-9;

    // 삼분탐색: f(t)가 유니모달(단 한 번 최솟값을 가진다고 가정)일 때 최소를 찾음.
    for (int iter = 0; iter < 200; iter++) {

        double mid1 = lowT + (highT - lowT) / 3;
        double mid2 = highT - (highT - lowT) / 3;

        // f(t)의 값이 더 작은 쪽(즉 최솟값에 가까운 쪽)으로 시간을 좁혀나감.
        if (f(mid1) < f(mid2))
            highT = mid2;
        else
            lowT = mid1;
    }

    // 최적의 시간에서의 bounding box 크기가 바로 정답.
    double ans = f(lowT);
    cout << fixed << setprecision(9) << ans << "\n";

    return 0;
}