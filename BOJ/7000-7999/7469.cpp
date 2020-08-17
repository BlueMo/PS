// 7469: K번째 수

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n, m, a, u, v, k, tree_size = 1;
vector<int> tree[1<<18];

void updateST(int idx, int val)
{
	idx += tree_size;
	while (idx >= 1)
	{
		tree[idx].push_back(val);
		idx >>= 1;	
	}
}

int num_underK(int l, int r, int val)
{
	int cnt = 0;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			cnt += upper_bound(tree[l].begin(), tree[l].end(), val) - tree[l].begin();
			l++;
		}
		if (~r & 1)
		{
			cnt += upper_bound(tree[r].begin(), tree[r].end(), val) - tree[r].begin();
			r--;
		}
		l >>= 1, r >>= 1;
	}
	return cnt;
}

int paraSearch(int val)
{
	int r = 1000000000, l = -r;
	
	while (l <= r)
	{
		int mid = (l+r)>>1;
		if (num_underK(u-1, v-1, mid) < val) l = mid + 1;
		else r = mid - 1;
	}
	return l;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	while(tree_size < n) tree_size <<= 1;
	for (int i = 0; i < n; ++i)
	{
		cin >> a;
		updateST(i, a);
	}
	for (int i = 0; i < tree_size; ++i) sort(tree[i].begin(), tree[i].end());
	
	while (m--)
	{
		cin >> u >> v >> k;
		cout << paraSearch(k) << "\n";
	}
	return 0;
}