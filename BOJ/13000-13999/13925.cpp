// 13925: 수열과 쿼리 13

#include<iostream>
#include<algorithm>
#define MOD 1000000007
using namespace std;
typedef long long ll;

int N, M, a, q, x, y, v;
struct ST
{
	ll v, lz = 0, lz2 = 1;	// value, +, *
	
	void update(int l, int r)
	{
		v = (lz2 * v + (r - l + 1) * lz) % MOD;
	}
	void push_lazy(int add, int mul)
	{
		lz = (lz * mul + add) % MOD;
		lz2 = (lz2 * mul) % MOD;
	}
	void clear()
	{
		lz = 0, lz2 = 1;
	}
}tree[1<<19];

void propST(int node, int l, int r)
{
	if (!tree[node].lz && tree[node].lz2 == 1) return;
	
	tree[node].update(l, r);
	if (l != r)
	{
		tree[node*2].push_lazy(tree[node].lz, tree[node].lz2);
		tree[node*2+1].push_lazy(tree[node].lz, tree[node].lz2);
	}
	
	tree[node].clear();
}

ll updateST(int node, int s, int e, int l, int r, int add, int mul)
{
	propST(node, l, r);
	if (r < s || l > e) return tree[node].v;
	if (l >= s && r <= e)
	{
		tree[node].push_lazy(add, mul);
		propST(node, l, r);
		return tree[node].v;
	}
	
	int mid = (l+r)>>1;
	return tree[node].v = (updateST(node*2, s, e, l, mid, add, mul) + updateST(node*2+1, s, e, mid+1, r, add, mul)) % MOD;
}

ll getSum(int node, int s, int e, int l, int r)
{
	propST(node, l, r);
	if (r < s || l > e) return 0;
	if (l >= s && r <= e) return tree[node].v;
	
	int mid = (l+r)>>1;
	return (getSum(node*2, s, e, l, mid) + getSum(node*2+1, s, e, mid+1, r)) % MOD;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		cin >> a;
		updateST(1, i, i, 1, N, a, 1);
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q;
		if (q == 1)
		{
			cin >> x >> y >> v;
			updateST(1, x, y, 1, N, v, 1);
		}
		else if (q == 2)
		{
			cin >> x >> y >> v;
			updateST(1, x, y, 1, N, 0, v);
		}
		else if (q == 3)
		{
			cin >> x >> y >> v;
			updateST(1, x, y, 1, N, v, 0);
		}
		else
		{
			cin >> x >> y;
			cout << getSum(1, x, y, 1, N) << "\n";
		}
	}
	return 0;
}