#include <cstdio>
#include <vector>
using namespace std;
#define ll long long

int N;
vector<ll> tree;
int fake_map[1000001] = {0,};

void init() {
	scanf("%d", &N);
	for (int i=0, tmp; i<N; i++) {
		scanf("%d", &tmp);
		fake_map[tmp] = i;
	}
	tree.assign(4*N, 0);
}

void update_tree(int node, int l, int r, int idx) {
	if (idx<l || idx>r) return;

	if (idx==r && idx==l) {
		tree[node] = 1;
		return;
	}

	int mid = (r+l)/2;
	tree[node]++;
	update_tree(node*2, l, mid, idx);
	update_tree(node*2+1, mid+1, r, idx);
	return;
}

ll make_sum(int node, int s, int e, int l, int r) {
	if (r<s || e<l) return 0;
	if (s<=l && r<=e) return tree[node];

	int mid = (r+l)/2;
	return make_sum(node*2, s, e, l, mid)+make_sum(node*2+1, s, e, mid+1, r);
}

int main () {
	ll ans = 0;
	init();
	for (int i=0, tmp; i<N; i++) {
		scanf("%d", &tmp);
		ans += make_sum(1, fake_map[tmp], N-1, 0, N-1);
		update_tree(1, 0, N-1, fake_map[tmp]);
	}
	printf("%lld\n", ans);
	return 0;
}