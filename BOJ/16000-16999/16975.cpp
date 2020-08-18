// 16975: 수열과 쿼리 21

#include<iostream>
using namespace std;
typedef long long ll;

int N, M, q, u, v, k, tree_size = 1;
long long tree[1<<18];

void addK(int l, int r, int k)
{
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			tree[l] += k;
			l++;
		}
		if (~r & 1)
		{
			tree[r] += k;
			r--;
		}
		l >>= 1, r >>= 1;
	}
}

ll getValue(int idx)
{
	ll val = 0;
	idx += tree_size;
	
	while (idx >= 1)
	{
		val += tree[idx];
		idx >>= 1;
	}
	return val;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 0; i < N; ++i)
		cin >> tree[tree_size + i];
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q >> u;
		if (q == 1)
		{
			cin >> v >> k;
			addK(u-1, v-1, k);
		}
		else cout << getValue(u-1) << "\n";
	}
	return 0;
}