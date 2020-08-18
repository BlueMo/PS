// 18436: 수열과 쿼리 37

#include<iostream>
using namespace std;

int N, M, a[100001], q, u, v, tree_size = 1;
int tree[1<<18];

void updateST(int idx, int val)		// count odd
{
	int t;
	if ( (a[idx] & 1)^(val & 1) )
	{
		t = (val & 1)?1:-1;
		a[idx] = val;				// update a[] when state(even,odd) is changed
		idx += tree_size;
		while (idx >= 1)
		{
			tree[idx] += t;
			idx >>= 1;
		}
	}
}

int cnt_odd(int l, int r)
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
		cin >> u;
		updateST(i, u);
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q >> u >> v;
		if (q == 1) updateST(u-1, v);
		else if (q == 2) cout << (v-u+1)-cnt_odd(u-1, v-1) << "\n";
		else cout << cnt_odd(u-1, v-1) << "\n";
	}
	return 0;
}