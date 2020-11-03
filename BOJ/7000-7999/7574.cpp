// 7574: 개구리

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

struct P
{
	int x, y, idx;
	bool operator < (const P &a) const { return x < a.x; }
}p[100002];

vector<int> pIdx;
int N, r, d, a, b, tree_size=1, par[100002], tree[1<<21], maxD;

int get_idx(int v){ return lower_bound(pIdx.begin(), pIdx.end(), v) - pIdx.begin(); }

void updateST(int idx, int v)
{
	int l, r;
	idx += tree_size;
	tree[idx] = v;
	
	while (idx > 1)
	{
		idx >>= 1;
		l = tree[idx<<1], r = tree[(idx<<1)|1];
		
		if (p[l].x > p[r].x) tree[idx] = l;
		else tree[idx] = r;
	}
}

int get_maxIdx(int l, int r)
{
	l += tree_size, r += tree_size;
	int ans = N;
	while (l <= r)
	{
		if (l & 1)
		{
			if (p[ans].x < p[tree[l]].x) ans = tree[l];
			l++;
		}
		if (~r & 1)
		{
			if (p[ans].x < p[tree[r]].x) ans = tree[r];
			r--;
		}
		l >>= 1, r >>= 1;
	}
	return ans;
}

int findParent(int x)
{
	if (x == par[x]) return x;
	return par[x] = findParent(par[x]);
}

void unionSet(int u, int v)
{
	u = findParent(u);
	v = findParent(v);
	par[v] = u;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> r;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 1; i <= tree_size+N; ++i)
		tree[i] = N;
	for (int i = 0; i < N; ++i)
	{
		cin >> p[i].x >> p[i].y;
		pIdx.push_back(p[i].y);
		par[i] = p[i].idx = i;
	}
	sort(pIdx.begin(), pIdx.end());
	sort(p, p+N);
	p[N].x = -1;
	cin >> d;
	
	for (int i = 0; i < N; ++i)
	{
		int t = get_idx(p[i].y);
		a = get_idx(p[i].y - r), b = get_idx(p[i].y + r);
		if (pIdx[b] > p[i].y + r) b--; 
		a = get_maxIdx(a, t);
		b = get_maxIdx(t, b);
		
		if (a != N && p[i].x - p[a].x <= r + d)
			unionSet(p[i].idx, p[a].idx);
		if (b != N && p[i].x - p[b].x <= r + d)
			unionSet(p[i].idx, p[b].idx);
		updateST(t, i);
	}
	
	pIdx.clear();
	for (int i = 1; i <= tree_size+N; ++i)
		tree[i] = N;
	
	for (int i = 0; i < N; ++i)
	{
		swap(p[i].x, p[i].y);
		pIdx.push_back(p[i].y);
	}
	sort(pIdx.begin(), pIdx.end());
	sort(p, p+N);
	p[N].x = -1;
	
	for (int i = 0; i < N; ++i)
	{
		int t = get_idx(p[i].y);
		a = get_idx(p[i].y - r), b = get_idx(p[i].y + r);
		if (pIdx[b] > p[i].y + r) b--;
		a = get_maxIdx(a, t);
		b = get_maxIdx(t, b);
		
		if (a != N && p[i].x - p[a].x <= r + d)
			unionSet(p[i].idx, p[a].idx);
		if (b != N && p[i].x - p[b].x <= r + d)
			unionSet(p[i].idx, p[b].idx);
		updateST(t, i);
	}
	
	for (int i = 0; i < N; ++i)
	{
		if (findParent(par[p[0].idx]) == findParent(par[p[i].idx]))
			maxD = max(maxD, p[i].x + p[i].y + 2*r);
	}
	
	cout << maxD;
	return 0;
}