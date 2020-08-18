// 14438: 수열과 쿼리 17

#include<iostream>
#define MIN(a,b) (((a)>(b))?(b):(a))
#define INF 0x7fffffff
using namespace std;

int N, M, a, q, u, v, tree_size = 1;
int tree[1<<18];

void updateST(int idx, int val)
{
	idx += tree_size;
	tree[idx] = val;
	while (idx > 1)
	{
		tree[idx>>1] = MIN(tree[idx], tree[idx^1]);
		idx >>= 1;
	}
}

int getMin(int l, int r)
{
	int ans = INF;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			ans = MIN(ans, tree[l]);
			l++;
		}
		if (~r & 1)
		{
			ans = MIN(ans, tree[r]);
			r--;
		}
		l >>= 1 , r >>= 1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 1; i < tree_size + N; ++i) tree[i] = INF;
	
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		updateST(i, a);
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q >> u >> v;
		if (q == 1) updateST(u-1, v);
		else cout << getMin(u-1, v-1) << "\n";
	}
	return 0;
}