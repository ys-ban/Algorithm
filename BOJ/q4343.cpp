#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct {
	int a, b;
	double cost;
}EDGE;

typedef struct {
	double x, y;
}POINT;

bool operator<(EDGE A, EDGE B) {
	return A.cost < B.cost;
}


int T;
int S, P;
int root[500];
bool satellite[500];
vector<POINT> O;
vector<EDGE> edge;
vector<EDGE> MST;
bool excluded[500];

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

double dist(POINT A, POINT B) {
	double dx = A.x-B.x;
	double dy = A.y-B.y;
	return sqrt(dx*dx+dy*dy);
}

void init() {
	O.clear();
	edge.clear();
	MST.clear();
	for (int i=0; i<500; i++) {satellite[i]=false;excluded[i]=false;}

	scanf("%d%d", &S, &P);
	POINT tmp;
	for (int i=0; i<P; i++) {
		scanf("%lf%lf", &tmp.x, &tmp.y);
		O.push_back(tmp);
		root[i] = i;
	}
}

void make_edge() {
	double d;
	EDGE E;
	for (int i=0; i<P; i++) {
		for (int j=i+1; j<P; j++) {
			E.a = i;
			E.b = j;
			E.cost = dist(O[i], O[j]);
			edge.push_back(E);
		}
	}
	sort(edge.begin(), edge.end());
}

double make_MST() {
	int n_edge = 0;

	for (int i=0, a, b; i<edge.size(); i++) {
		a = find_root(edge[i].a);
		b = find_root(edge[i].b);
		if (a!=b) {
			union_root(edge[i].a, edge[i].b);
			n_edge++;
			MST.push_back(edge[i]);
		}
		if (n_edge==(P-S)) break;
	}
	return MST[MST.size()-1].cost;
}


int main () {
	scanf("%d", &T);
	while (T--) {
		init();
		make_edge();
		printf("%.2lf\n", make_MST());
		/*for (int i=0; i<edge.size(); i++) {
			printf("%d %d %lf\n", edge[i].a, edge[i].b, edge[i].cost);
		}*/
	}
	return 0;
}