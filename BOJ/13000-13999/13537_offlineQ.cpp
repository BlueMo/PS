// 13537: 수열과 쿼리 1
// Offline query

#include<iostream>
#include<algorithm>
using namespace std;

struct Q
{
	int l, r, k, idx;
	
	bool operator<(const Q &a) const
	{
		return this->k > a.k;	
	}
}q[100001];

struct A
{
	int v, idx;
	
	bool operator<(const A &a) const
	{
		return this->v < a.v;
	}
}a[100001];

int N, M, ans[100001], tree_size = 1;
int tree[1<<18];


void updateST(int idx)
{
	idx += tree_size;
	
	while (idx >= 1)
	{
		tree[idx]++;
		idx >>= 1;
	}
}

int getCnt(int l, int r)
{
	int cnt = 0;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1) cnt += tree[l++];
		if (~r & 1) cnt += tree[r--];
		
		l >>= 1, r >>= 1;
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	while (tree_size < N) tree_size <<= 1;
	
	for (int i = 0; i < N; ++i)
	{
		cin >> a[i].v;
		a[i].idx = i;
	}
	sort(a, a+N);
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q[i].l >> q[i].r >> q[i].k;
		q[i].idx = i;
	}
	sort(q, q+M);
	
	int p, s = N-1;
	A tmp;
	tmp.idx = 0;
	for (int i = 0; i < M; ++i)
	{
		tmp.v = q[i].k;
		p = upper_bound(a, a+s+1, tmp) - a;
		for (int j = s; j >= p; --j)
			updateST(a[j].idx);
		s = p-1;
		ans[q[i].idx] = getCnt(q[i].l-1, q[i].r-1);
	}
	for (int i = 0; i < M; ++i)
		cout << ans[i] << "\n";
	return 0;
}