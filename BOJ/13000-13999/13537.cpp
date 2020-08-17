// 13537: 수열과 쿼리 1

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N, M, a, u, v, k, tree_size = 1;
vector<int> tree[1<<18];

void updateST(int idx, int val)
{
	idx += tree_size;
	tree[idx].push_back(val);
	while (idx > 1)
	{
		idx >>= 1;
		tree[idx].push_back(val);
	}
}

int num_overK(int l, int r)
{
	int ans = 0;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			ans += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), k);
			l++;
		}
		if (~r & 1)
		{
			ans += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), k);
			r--;
		}
		l >>= 1, r >>= 1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		updateST(i, a);
	}
	cin >> M;
	
	for (int i = 1; i <= tree_size; ++i)
		sort(tree[i].begin(), tree[i].end());
	while (M--)
	{
		cin >> u >> v >> k;
		u--, v--;
		cout << num_overK(u, v) << "\n";
	}
	return 0;
}