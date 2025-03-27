#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXSIDE 300
#define ll long long
using namespace std;

ll dp[50][MAXSIDE][MAXSIDE];
string word;
char board[MAXSIDE][MAXSIDE];
int Y, X, L;
int dydx[2][4] = { {-2,-2,2,2}, {-2,2,-2,2} };

ll pMod(ll in) {
	while (in < 0) in += MOD;
	return in % MOD;
}

// (y1, x1) ~ (y2, x2) 의 총 합. 
// 계산은 누적합을 이용한다 
//	sum of (y1, x1) ~ (y2, x2) is 
//	prefixSum(y2,x2) - prefixSum(y1-1,x2) -prefixSum(y2,x1-1) + prefixSum(y1-1,x2-1)
ll Sum2D(int idx, int y1, int x1, int y2, int x2) {
	if (y1 == y2 && x1 == x2) {
		if (y1 < 0 || y1 >= Y || x1 < 0 || x1 >= X)
			return 0;//한점용 
	}
	if (y1 < 0) y1 = 0;
	if (x1 < 0) x1 = 0;
	if (y2 >= Y) y2 = Y - 1;
	if (x2 >= X) x2 = X - 1;

	ll ret = 0;
	ret += dp[idx][y2][x2];
	if (y1 > 0) ret -= dp[idx][y1 - 1][x2];
	if (x1 > 0) ret -= dp[idx][y2][x1 - 1];
	if (y1 > 0 && x1 > 0)  
		ret += dp[idx][y1 - 1][x1 - 1];
	return pMod(ret);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> Y >> X >> L;
	cin >> word;
	L = word.length();
	 
	for (int i = 0; i < Y; ++i)
		cin >> board[i];

	// index 0 일때 누적합을 미리 계산
	for (int i = 0; i < Y; ++i) {
		for (int j = 0; j < X; ++j) {
			if (board[i][j] == word[0])	dp[0][i][j] = 1;
			if (j > 0) dp[0][i][j] += dp[0][i][j - 1];//왼쪽더하고
			if (i > 0) dp[0][i][j] += dp[0][i - 1][j];//위쪽더하고
			if (i > 0 && j > 0) dp[0][i][j] -= dp[0][i - 1][j - 1];//중복제거
		}
	}

	// 1부터 dp를 계산하는데 위에서 계산한 누적합을 이용하여 
	// 유니콘구간합을 계산한다
	for (int i = 1; i < L; ++i) {
		for (int j = 0; j < Y; ++j) {
			for (int k = 0; k < X; ++k) {
				if (board[j][k] == word[i]) {
					dp[i][j][k] = Sum2D(i - 1, 0, 0, Y - 1, X - 1);
					dp[i][j][k] -= Sum2D(i - 1, 0, k - 1, Y - 1, k + 1); //3x세로 교차선 빼고
					dp[i][j][k] -= Sum2D(i - 1, j - 1, 0, j + 1, X - 1); //3x가로 교차선 빼고
					dp[i][j][k] += Sum2D(i - 1, j - 1, k - 1, j + 1, k + 1);//3x3가운데 정사각형 더하고
					
					//5x5 끝머리 1블록 4개 뺌.대각선으로 2칸.
					for (int dir = 0; dir < 4; dir++) {
						int ny = j + dydx[0][dir];
						int nx = k + dydx[1][dir];
						dp[i][j][k] -= Sum2D(i - 1, ny, nx, ny, nx);
					}
					
					dp[i][j][k] = pMod(dp[i][j][k]);
				}

			}
		}

		// 다음dp를 구하기 위한 누적합 계산
		for (int j = 0; j < Y; ++j) {
			for (int k = 0; k < X; ++k) {
				if (k > 0) dp[i][j][k] += dp[i][j][k - 1];//왼쪽더하고
				if (j > 0)  dp[i][j][k] += dp[i][j - 1][k];//위쪽더하고
				if (j > 0 && k > 0) dp[i][j][k] -= dp[i][j - 1][k - 1];//중복제거
				dp[i][j][k] = pMod(dp[i][j][k]);
			}
		}
	}

	cout << dp[L-1][Y-1][X-1];
}

/*
*누적합(prefix sum)방식을 사용하여 dp를 계산한다.

str : ab
arr : bbaa
  b 0 1 2 3
a --------------------
0|  0 0 1 1
1|  0 1 0 0 => 4

1차원에서 dp[a][b] : b위치에서 a번째 str의 글자가 존재할 수 있는 경우의 수
dp[a][b] = if (str[a] == arr[b]) {
				dp[a][b] = dp[a-1][b+1] + dp[a-1][b-1];
			}

유니콘문제도 위와 동일하게 dp[l][y][x] : y,x위치에서 str의 l번째 글자가 존재할 수 있는 경우의 수
if (str[l] == arr[y][x]) {
		dp[l][y][x] = dp[l-1][all sum of yx의 이전 유니콘 위치]
	}
=> 현재 yx에서 유니콘 위치에 해당하는 모든 구역의 합을 더하면된다. 이과정에서 2차원 누적합이 필요
그림 참조 : https://nahwasa.com/entry/%EC%9E%90%EB%B0%94-%EB%B0%B1%EC%A4%80-1048-%EC%9C%A0%EB%8B%88%EC%BD%98-java



아래는 누적합 잠시 리마인드
==================================================================================
- 1차원 기존방식)
arr = {1,2,3,4,5...,N} N개원소 배열의 구간합을 M번 구할때

int getRangedSum(int s, int e) {
	int sum = 0;
	for (int i=s;i<=e;i++)
		sum+=arr[i];
	return sum;
}
- 이방법은 O(NM)... N, M이 십만만되도, 10^10번을 넘어가 시간초과가 된다.


- 1차원 누적합 방식)
int getPrefixSum(int N) {
	int prefixSum[N+1];
	prefixSum[0] = arr[0];
	for (int i = 1; i <= N; i++) {
		prefixSum[i] = prefixSum[i-1] + arr[i];
	}
	return prefixSum;
}
arr			= 1	2 3	4  5
prefixSum	= 1	3 6	10 15... <- 1~N까지 누적합을 저장
s~e구간합은 prefixSum[e] - prefixSum[s-1]
e.g) arr[1]~arr[2] 까지 구간합은 prefixSum[2] - prefixSum[0] = 6 - 1 = 5

- 기존방식 시간복잡도 : O(NM)
- 누적합방식 시간복잡도 : O(N+M)



2차원 누적합)
(s1,s2) ~ (e1,e2) 까지 구간 합은
prefixSum[e1][e2] - prefixSum[e1][s2-1] - prefixSum[s1-1][e2] + prefixSum[s1-1][s2-1]


- 0,0 배열 추가 하면 아래와 같이
prefixSum[x][y]
for (int i = 1; i <= r; i++) {
	for (int j = 1; j <= c; j++) {
		prefixSum[i][j] = prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1] + arr[i][j];
	}
}

- 0,0 배열 따로 추가 안하고 싶다?
   // 누적합 계산
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// 현재 값
			prefixSum[i][j] = arr[i][j];

			// 왼쪽 값 추가
			if (j > 0)
				prefixSum[i][j] += prefixSum[i][j - 1];

			// 위쪽 값 추가
			if (i > 0)
				prefixSum[i][j] += prefixSum[i - 1][j];

			// 중복으로 더한 왼쪽 위 값을 빼줌
			if (i > 0 && j > 0)
				prefixSum[i][j] -= prefixSum[i - 1][j - 1];
		}
	}

==================================================================================
*/
