#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int bitMask[10][1 << 10];
char board[10][10];

void dfs(const int index, std::string& line);
void solve(void);

int main(void)
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	

	int testCase;
	std::cin >> testCase;
	for (int t = 0; t < testCase; t++)
		solve();
}

void dfs(std::vector<std::string>& lines, int (& dfsArray)[10], int index, int& m)
{
	if (m == index)
	{
		std::string str;
		for (int a : dfsArray)
			str += std::to_string(a);
		
		lines.push_back(str);
		return;
	}
	
	dfsArray[index] = 0;
	dfs(lines, dfsArray, index + 1, m);

	if (0 < index && dfsArray[index - 1] != 0)
		return;

	dfsArray[index] = 1;
	dfs(lines, dfsArray, index + 1, m);
}

int dp(std::vector<std::string>& lines, int lineNumber, int beforeBits, int& n, int& m)
{
	if (n == lineNumber)
		return 0;

	if (-1 < bitMask[lineNumber][beforeBits])
		return bitMask[lineNumber][beforeBits];

	int answer = 0;
	for (auto line : lines)
	{
		int bits = 0;
		int count = 0;

		for (int i = 0; i < m; i++)
		{
			if ('0' == line[i])
				continue;

			if ('x' == board[lineNumber][i])
				continue;

			if (0 < i && beforeBits & (1 << (i - 1)))
				continue;
			
			if (i < m && beforeBits & (1 << (i + 1)))
				continue;

			count++;
			bits |= (1 << i);
		}

		answer = std::max(answer, dp(lines, lineNumber + 1, bits, n, m) + count);
	}

	bitMask[lineNumber][beforeBits] = answer;
	return answer;
}

void solve(void)
{
	std::fill(bitMask[0], bitMask[0] + (10 * (1 << 10)), -1);
	std::fill(board[0], board[0] + (10 * 10), 0);

	int n, m;
	std::cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> board[i][j];

	int dfsArray[10];
	std::vector<std::string> lines;
	dfs(lines, dfsArray, 0, m);

	std::cout << dp(lines, 0, 0, n, m) << '\n';
}
