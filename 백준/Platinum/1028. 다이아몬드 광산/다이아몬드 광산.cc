#include <bits/stdc++.h>
using namespace std;

int arr[1508][1508]; // 입력 배열
int ld[808][808]; // 현재 지점까지 왼쪽 아래 대각선 최대 크기 
int rd[808][808]; 
int lu[808][808]; 
int ru[808][808]; 


int main() {
	cin.tie(0)->sync_with_stdio(0);

	int R, C;
	cin >> R >> C;

	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			char ch;
			cin >> ch;
			arr[i][j] = ch - '0'; 
		}
	}

	for (int i = R; i >= 1; --i) {
		for (int j = 1; j <= C; ++j) {
			if (arr[i][j] == 1) {
				ld[i][j] = ld[i + 1][j - 1] + 1;
				rd[i][j] = rd[i + 1][j + 1] + 1;
			}
		}
	}

	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			if (arr[i][j] == 1) {
				lu[i][j] = lu[i - 1][j - 1] + 1;
				ru[i][j] = ru[i - 1][j + 1] + 1;
			}
		}
	}

	int ans = 0, k;
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			// 현재 지점부터 왼쪽아래, 오른쪽아래크기가 k로 보장될때 
			for (k = 1; k <= min(ld[i][j], rd[i][j]); k++) {
				// 반대편 아래 지점에서 왼쪽위, 왼쪽아래가 k로 보장되는지 확인하면된다. 
				if (i+(k-1)*2 <= R) {
					if (min(lu[i + (k-1)*2][j], ru[i + (k - 1)*2][j]) >= k) {
						ans = max(ans, k);
					}
				}
			}
		}
	}

	cout << ans;
	return 0;
}
