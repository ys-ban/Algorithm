#include <cstdio>
#include <vector>
#include <queue>
#pragma warning(disable:4996)
#define NO_VISIT (1234567890)

using namespace std;

int N, M;
int sx, sy, ex, ey;
int board[1000][1000];
int dp[2][1000][1000];
int di[2][4] = { {0, 0, 1, -1}, {1, -1, 0, 0} };
int min_dist_col[2][1000];
int min_dist_row[2][1000];
vector<int> adj[1000000];

void init() {
	scanf("%d%d", &N, &M);
	scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
	--sx, --sy, --ex, --ey;
	for (int n = 0; n < N; ++n) {
		for (int m = 0; m < M; ++m) {
			scanf("%d", &board[n][m]);
			dp[0][n][m] = dp[1][n][m] = NO_VISIT;
		}
	}
	for (int i = N * M - 1; i >= 0; --i) adj[i].clear();
}

int f(const int& x, const int& y) { return x * M + y; }
int gx(const int& i) { return i / M; }
int gy(const int& i) { return i % M; }

int solve_bfs() {
	init();
	int cur_x, cur_y, nxt_x, nxt_y, cur, nxt;
	queue<int> q;
	dp[0][sx][sy] = 0;
	q.push(f(sx, sy));
	for (int n = 0; n < N; ++n) {
		for (int m = 0; m < M; ++m) {
			for (int i = 0; i < 4; ++i) {
				nxt_x = n + di[0][i] * board[n][m]; nxt_y = m + di[1][i] * board[n][m];
				if (nxt_x < 0 || nxt_x >= N || nxt_y < 0 || nxt_y >= M) continue;
				adj[f(nxt_x, nxt_y)].push_back(f(n, m));
			}
		}
	}
	while (!q.empty()) {
		cur = q.front(); q.pop();
		cur_x = gx(cur), cur_y = gy(cur);
		for (int i = 0; i < 4; ++i) {
			nxt_x = cur_x + di[0][i] * board[cur_x][cur_y], nxt_y = cur_y + di[1][i] * board[cur_x][cur_y];
			if (nxt_x < 0 || nxt_x >= N || nxt_y < 0 || nxt_y >= M) continue;
			if (dp[0][nxt_x][nxt_y] != NO_VISIT) continue;
			nxt = f(nxt_x, nxt_y);
			dp[0][nxt_x][nxt_y] = dp[0][cur_x][cur_y] + 1;
			q.push(nxt);
		}
	}
	dp[1][ex][ey] = 0;
	q.push(f(ex, ey));
	while (!q.empty()) {
		cur = q.front(); q.pop();
		cur_x = gx(cur); cur_y = gy(cur);
		for (int i=0; i<adj[cur].size(); ++i) {
			nxt = adj[cur][i];
			nxt_x = gx(nxt), nxt_y = gy(nxt);
			if (dp[1][nxt_x][nxt_y] != NO_VISIT) continue;
			dp[1][nxt_x][nxt_y] = dp[1][cur_x][cur_y] + 1;
			q.push(nxt);
		}
	}
	for (int i = 0; i < N; ++i) min_dist_row[0][i] = min_dist_row[1][i] = NO_VISIT;
	for (int i = 0; i < M; ++i) min_dist_col[0][i] = min_dist_col[1][i] = NO_VISIT;
	for (int n = 0; n < N; ++n) {
		for (int m = 0; m < M; ++m) {
			min_dist_row[0][n] = (dp[0][n][m] < min_dist_row[0][n] ? dp[0][n][m] : min_dist_row[0][n]);
			min_dist_row[1][n] = (dp[1][n][m] < min_dist_row[1][n] ? dp[1][n][m] : min_dist_row[1][n]);
		}
	}
	for (int m = 0; m < M; ++m) {
		for (int n = 0; n < N; ++n) {
			min_dist_col[0][m] = (dp[0][n][m] < min_dist_col[0][m] ? dp[0][n][m] : min_dist_col[0][m]);
			min_dist_col[1][m] = (dp[1][n][m] < min_dist_col[1][m] ? dp[1][n][m] : min_dist_col[1][m]);
		}
	}
	int ret = NO_VISIT, cndd;
	for (int n = 0; n < N; ++n) {
		if (min_dist_row[0][n] == NO_VISIT || min_dist_row[1][n] == NO_VISIT) continue;
		cndd = min_dist_row[0][n] + min_dist_row[1][n] + 1;
		ret = cndd < ret ? cndd : ret;
	}
	for (int m = 0; m < M; ++m) {
		if (min_dist_col[0][m] == NO_VISIT || min_dist_col[1][m] == NO_VISIT) continue;
		cndd = min_dist_col[0][m] + min_dist_col[1][m] + 1;
		ret = cndd < ret ? cndd : ret;
	}
	cndd = dp[0][ex][ey];
	ret = cndd < ret ? cndd : ret;
	return ret == NO_VISIT ? -1 : ret;
}

int main() {
	printf("%d\n", solve_bfs());
	return 0;
}