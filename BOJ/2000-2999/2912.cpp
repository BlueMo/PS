// 2912: 백설공주와 난쟁이

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N, C, M, tree_size=1, a, ans[100], u, v;
vector<int> c_idx[100001];
int getCnt(int c, int l, int r)
{
	if (!c) return 0;
	return upper_bound(c_idx[c].begin(), c_idx[c].end(), r) - upper_bound(c_idx[c].begin(), c_idx[c].end(), l-1);
}

struct ST
{
	int l, r, v;
	
	int mid(){ return (r-l+1)>>1; }
	int vCnt(int _v){ return getCnt(_v, l, r); }
}tree[1<<21];

void buildST()
{
	int l, r, mid;
	for (int i = tree_size-1; i >= 1; --i)
	{
		l = i<<1;
		r = l|1;
		tree[i].l = tree[l].l;
		if (tree[r].r) tree[i].r = tree[r].r;
		else tree[i].r = tree[l].r;
		mid = tree[i].mid();
		if (tree[i].vCnt(tree[l].v) > mid)
			tree[i].v = tree[l].v;
		else if (tree[i].vCnt(tree[r].v) > mid)
			tree[i].v = tree[r].v;
	}
}

void is_beauty(int l, int r)
{
	int L = l, R = r, mid, cnt = 0;
	mid = (R-L+1) >> 1;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			if (tree[l].v) ans[cnt++] = tree[l].v;
			l++;
		}
		if (~r & 1)
		{
			if (tree[r].v) ans[cnt++] = tree[r].v;
			r--;
		}
		l >>= 1, r >>= 1;
	}
	for (int i = 0; i < cnt; ++i)
	{
		if (getCnt(ans[i], L, R) > mid)
		{
			cout << "yes " << ans[i] << "\n";
			return;
		}
	}
	cout << "no\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> C;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		c_idx[a].push_back(i);
		tree[tree_size + i] = {i, i, a};
	}
	buildST();
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> u >> v;
		is_beauty(u-1, v-1);
	}
	return 0;
}