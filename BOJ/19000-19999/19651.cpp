// 19651: 수열과 쿼리 39
// fail1: (r-1)*b overflow
// fail2: update query: r < N -> r <= N

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int N, M, a, b, q, l, r;

struct ST
{
	ll lv, rv, lz;
	int lmax, rmax, ans, size;
	
	void update(){ lv += lz, rv += lz; }
	void push_lazy(ll val){ lz += val; }
	void clear(){ lz = 0; }
	
	void merge(ST a)
	{
		lv = a.lv;
		rv = a.rv;
		lmax = a.lmax;
		rmax = a.rmax;
		ans = a.ans;
		size = a.size;
	}
}tree[1<<19], nullST;

void propST(int node, int l, int r)
{
	if (!tree[node].lz) return;

	tree[node].update();
	if (l != r)
	{
		tree[node<<1].push_lazy(tree[node].lz);
		tree[(node<<1)|1].push_lazy(tree[node].lz);
	}
	tree[node].clear();
}

ST mergeST(ST lnode, ST rnode)
{
	if (!lnode.size) return rnode;
	if (!rnode.size) return lnode;
	
	ST ret;
	ret.lv = lnode.lv;
	ret.lmax = lnode.lmax;
	ret.rv = rnode.rv;
	ret.rmax = rnode.rmax;
	ret.ans = max(lnode.ans, rnode.ans);
	ret.size = lnode.size + rnode.size;		// real need?
	
	if (lnode.rv == rnode.lv && ret.ans < lnode.rmax + rnode.lmax)
	{
		ret.ans = lnode.rmax + rnode.lmax;
		if (lnode.size == lnode.rmax) ret.lmax = ret.ans;
		if (rnode.size == rnode.lmax) ret.rmax = ret.ans;
	}
	return ret;
}

ST updateST(int node, int l, int r, int s, int e, ll val)
{
	propST(node, l, r);
	if (r < s || l > e)	return tree[node];
	if (s <= l && r <= e)
	{
		if (!tree[node].size)
			tree[node].lmax = tree[node].rmax = tree[node].ans = tree[node].size = 1;
		tree[node].push_lazy(val);
		propST(node, l, r);
		return tree[node];
	}
	
	int mid = (l+r)>>1;
	ST ret = mergeST(updateST(node<<1, l, mid, s, e, val), updateST((node<<1)|1, mid+1, r, s, e, val));
	tree[node].merge(ret);
	return tree[node];
}

ST getAns(int node, int l, int r, int s, int e)
{
	propST(node, l, r);
	if (r < s || l > e) return nullST;
	if (s <= l && r <= e) return tree[node];
	
	int mid = (l+r)>>1;
	return mergeST(getAns(node<<1, l, mid, s, e),
				   getAns((node<<1)|1, mid+1, r, s, e));
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	nullST.lmax = nullST.rmax = nullST.ans = nullST.size = 0;
	cin >> N;
	cin >> a;
	N--;
	for (int i = 1; i <= N; ++i)
	{
		cin >> b;
		updateST(1, 1, N, i, i, (ll)b-a);
		a = b;
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q;
		if (q == 1)
		{
			cin >> l >> r >> a >> b;
			if (l > 1) updateST(1, 1, N, l-1, l-1, a);
			updateST(1, 1, N, l, r-1, b);
			if (r <= N) updateST(1, 1, N, r, r, -a - 1LL*(r-l)*b);
		}
		else
		{
			cin >> l >> r;
			cout << getAns(1, 1, N, l, r-1).ans + 1 << "\n";
		}
	}
	return 0;
}