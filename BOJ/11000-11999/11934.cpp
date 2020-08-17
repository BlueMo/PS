// 11934: Fortune Telling 2

#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<cstring>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)>(b))?(b):(a))
using namespace std;
typedef long long ll;

int N, M, K[200001], tree_size = 1, maxST_size = 1;
int a[200001], b[200001];
int maxST[1<<21];
vector<int> card_idx, tree[1<<19];
ll ans;

int getcard_idx(int val)
{
	return lower_bound(card_idx.begin(), card_idx.end(), val) - card_idx.begin();
}

void updateMaxST(int idx, int val)		// build max seg tree
{
	idx += maxST_size;
	while (idx >= 1)
	{
		if (maxST[idx] >= val) break;
		maxST[idx] = val;
		idx >>= 1;
	}
}

void updateST(int idx, int val)		    // build merge sort tree
{
	idx += tree_size;
	while (idx >= 1)
	{
		tree[idx].push_back(val);
		idx >>= 1;
	}
}

int getMax(int l, int r)
{
	int max = -1;
	l += maxST_size, r += maxST_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			max = MAX(max, maxST[l]);
			l++;
		}
		if (~r & 1)
		{
			max = MAX(max, maxST[r]);
			r--;
		}
		l >>= 1, r >>= 1;
	}
	return max;
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
	
	cin >> N >> M;
	while (tree_size < M) tree_size <<= 1;
	for (int i = 0; i < N; ++i)
	{
		cin >> a[i] >> b[i];
		card_idx.push_back(a[i]);
		card_idx.push_back(b[i]);
	}
	for (int i = 0; i < M; ++i)
	{
		cin >> K[i];
		card_idx.push_back(K[i]);
	}
	sort(card_idx.begin(), card_idx.end());
	card_idx.erase(unique(card_idx.begin(), card_idx.end()), card_idx.end());
	memset(maxST, -1, sizeof(maxST));
	
	while (maxST_size < card_idx.size()) maxST_size <<= 1;
	for (int i = 0; i < M; ++i)
	{
		int t = getcard_idx(K[i]);
		updateST(i, t);
		updateMaxST(t, i);
	}
	for (int i = 1; i < tree_size; ++i) sort(tree[i].begin(), tree[i].end());
	
	int u, v, cnt;
	for (int i = 0; i < N; ++i)
	{
		u = getcard_idx(a[i]);
		v = getcard_idx(b[i]);
		if (u > v) swap(u, v);
		u = getMax(u, v-1);
		cnt = num_overK(u+1, M-1, v-1);
		if (u == -1)
		{
			if (cnt & 1) ans += b[i];
			else ans += a[i];
		}
		else
		{
			if (cnt & 1) ans += MIN(a[i], b[i]);
			else ans += MAX(a[i], b[i]);
		}
	}
	cout << ans;
	return 0;
}