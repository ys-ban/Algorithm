#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

int N, M, K, T;
int a;
int pos;
ll val, d;
int st, e;

ll arr[1000000];
ll tree[4000001];

ll init(int node, int start, int end)
{
	if (start==end) return tree[node] = arr[start];

	int mid = (start+end)/2;
	return tree[node] = init(node*2, start, mid) + init(node*2+1, mid+1, end);
}

void update(int node, int start, int end, int index, ll diff)
{
	if (start>index || end<index) return;

	tree[node] += diff;

	if (start==end) return;
	int mid = (start+end)/2;
	update(node*2, start, mid, index, diff);
	update(node*2+1, mid+1, end, index, diff);
}

ll sum(int node, int start, int end, int left, int right)
{
	if (right<start || end<left) return 0;
	if (start>=left&&right>=end) return tree[node];

	int mid = (start+end)/2;
	return sum(node*2, start, mid, left, right) + sum(node*2+1, mid+1, end, left, right);
}

int main ()
{
	vector<int> vvv;
	vvv.push_back(2);
	vvv.push_back(3);
	vvv.push_back(4);
	vvv.push_back(5);

	sort(vvv.begin(), vvv.end());
	for (int i=0; i<4; i++) {
		printf("%d\n", vvv[i]);
	}

	scanf("%d%d%d", &N, &M, &K);
	T = M+K;

	for (int i=0; i<N; i++) scanf("%lld", &arr[i]);

	init(1, 0, N-1);

	for (int t=0; t<T; t++)
	{
		scanf("%d", &a);
		if (a==1)
		{
			scanf("%d %lld", &pos, &val);
			d = val-arr[pos-1];
			arr[pos-1] = val;
			update(1, 0, N-1, pos-1, d);
		}
		else
		{
			scanf("%d%d", &st, &e);
			st--;
			e--;
			printf("%lld\n", sum(1, 0, N-1, st, e));
		}
	}
}
