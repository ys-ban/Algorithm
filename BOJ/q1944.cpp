#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
반영성
연세대학교 수학과
https://dontwannawork.tistory.com/

<백준 1944 복제 로봇>
종류 : MST, 최소신장트리
*/

typedef struct {
	int a, b;
	int cost;
}EDGE;

typedef struct {
	int x, y;
}POINT;

bool operator<(EDGE A, EDGE B) {
	return A.cost < B.cost;
}

int d[2][4] = {{1,0,-1,0},{0,1,0,-1}};

int N, M;
int board[50][50];
int root[252];
vector<POINT> K;
vector<EDGE> edge;

int find_root(int a) {
	if (root[a]==a) return a;

	return root[a] = find_root(root[a]);
}

void union_root(int a, int b) {
	int root_a = find_root(a);
	int root_b = find_root(b);

	root[root_a] = root_b;
	return;
}

void init() {
	scanf("%d%d", &N, &M);
	char tmp_board[55];
	POINT tmp_POINT;
	for (int i=0; i<N; i++) {
		scanf("%s", tmp_board);
		for (int j=0; j<N; j++) {
			if (tmp_board[j]-'K'==0) {
				tmp_POINT.x = i;
				tmp_POINT.y = j;
				K.push_back(tmp_POINT);
				board[i][j] = 0;
			} else if (tmp_board[j]-'S'==0) {
				tmp_POINT.x = i;
				tmp_POINT.y = j;
				K.push_back(tmp_POINT);
				board[i][j] = 0;
			} else if (tmp_board[j]-'1'==0) {
				board[i][j] = 1;
			} else {
				board[i][j] = 0;
			}
		}
	}
	for (int i=0; i<=M; i++) {
		root[i] = i;
	}
	return;
}

void make_edge () {
	int t[50][50];
	EDGE E;
	for (int i=0; i<=M; i++) {
		for (int l=0; l<N; l++) {for (int j=0; j<N; j++) {t[l][j] = -1;}}
		queue<POINT> q;
		POINT now, nxt;
		q.push(K[i]);
		t[K[i].x][K[i].y] = 0;
		while (!q.empty()) {
			now = q.front();
			q.pop();
			for (int j=0; j<4; j++) {
				nxt.x = now.x + d[0][j];
				nxt.y = now.y + d[1][j];
				if (nxt.x<0 || nxt.y<0 || nxt.x>=N || nxt.y>=N) continue;
				if (board[nxt.x][nxt.y]!=0) continue;
				if (t[nxt.x][nxt.y]<0) {
					t[nxt.x][nxt.y] = t[now.x][now.y]+1;
					q.push(nxt);
				} else {
					int tmp_t = t[now.x][now.y]+1;
					if (tmp_t<t[nxt.x][nxt.y]) {
						t[nxt.x][nxt.y] = tmp_t;
						q.push(nxt);
					}
				}
			}
		}
		for (int k=i+1; k<=M; k++) {
			if (t[K[k].x][K[k].y]==-1) continue;
			E.a = i;
			E.b = k;
			E.cost = t[K[k].x][K[k].y];
			edge.push_back(E);
		}
	}
	return;
}

int solve() {
	int ret = 0;
	sort(edge.begin(), edge.end());
	int n_edge = 0;
	for (int i=0, x, y; i<edge.size(); i++) {
		x = find_root(edge[i].a);
		y = find_root(edge[i].b);
		if (x!=y) {
			union_root(edge[i].a, edge[i].b);
			//printf("%d, %d joined\n", edge[i].a, edge[i].b);
			n_edge++;
			ret += edge[i].cost;
		}
		if (n_edge==M) break;
	}
	if (n_edge!=M) return -1;
	return ret;
}

int main () {
	init();
	make_edge();
	printf("%d\n", solve());
	/*for (int i=0; i<edge.size(); i++) {
		printf("a: %d / b: %d / cost: %d \n", edge[i].a, edge[i].b, edge[i].cost);
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}*/
	return 0;
}