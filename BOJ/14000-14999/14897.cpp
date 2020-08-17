// 14897: 서로 다른 수와 쿼리 1

#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<queue>
using namespace std;

int N, Q, a[1000001], tree_size = 1, u, v;
unordered_map<int, int> map;
vector<int> tree[1<<21];
queue<int> next_idx[1000001];

void updateST(int idx, int val)
{
	idx += tree_size;
	while (idx >= 1)
	{
		tree[idx].push_back(val);
		idx >>= 1;
	}
}

int num_overK(int l, int r, int val)
{
	int cnt = 0;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			cnt += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), val);
			l++;
		}
		if (~r & 1)
		{
			cnt += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), val);
			r--;
		}
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
	for (int i = 0; i < N; ++i)		// hashing
	{
		cin >> a[i];
		if (map.end() == map.find(a[i])) map[a[i]] = map.size();
		a[i] = map[a[i]];
		next_idx[a[i]].push(i);
	}
	
	for (int i = 0; i < N; ++i)
	{
		queue<int> &q = next_idx[a[i]];
		int h;
		q.pop();
		if (!q.empty()) h = q.front();
		else h = N;
		updateST(i, h);
	}
	for (int i = 1; i < tree_size; ++i) sort(tree[i].begin(), tree[i].end());
	
	cin >> Q;
	while (Q--)
	{
		cin >> u >> v;
		cout << num_overK(u-1, v-1, v-1) << "\n";
	}
	return 0;
}