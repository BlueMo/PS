// 14504: 수열과 쿼리 18
// fail1: endl TLE
// 2000ms 시간제한에서 1840ms 로 통과 -> 최적화 필요

#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

int N, M, l, r, k, t, sqrtN, b, sz, ans;
int a[100001];
int tree[320][200002];
vector<int> idx;

struct Q
{
	int l, r, k;
}q[100001];

int get_idx(int val)
{ 
	return lower_bound(idx.begin(), idx.end(), val) - idx.begin() + 1;
}

void updateFwT(int bN, int idx, int is_push=1)
{
	while (idx <= sz)
	{
		tree[bN][idx] += is_push;
		idx += idx & -idx;
	}
}

int getCnt(int bN, int idx)
{
	int cnt = 0;
	if (idx > sz) idx = sz;
	
	while (idx > 0)
	{
		cnt += tree[bN][idx];
		idx -= idx & -idx;
	}
	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	sqrtN = sqrt(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> a[i];
		idx.push_back(a[i]);
	}
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> t;
		if (t == 1)
			cin >> q[i].l >> q[i].r >> q[i].k;
		else
			cin >> q[i].l >> q[i].k;
		idx.push_back(q[i].k);
		q[i].l--;
		q[i].r--;
	}
	sort(idx.begin(), idx.end());
	idx.erase(unique(idx.begin(), idx.end()), idx.end());
	sz = idx.size() + 1;
	for (int i = 0; i < N; ++i) a[i] = get_idx(a[i]);
	for (int i = 0; i < M; ++i) q[i].k = get_idx(q[i].k);
	
	for (int i = 0; i <= sqrtN + 1; ++i)
	{
		int e = min((i+1)*sqrtN, N);
		for (int j = i*sqrtN; j < e; ++j) updateFwT(i, a[j]);
	}
	
	for (int i = 0; i < M; ++i)
	{
		if (q[i].r == -1)
		{
			l = q[i].l / sqrtN;
			updateFwT(l, a[q[i].l], -1);
			updateFwT(l, q[i].k);
			a[q[i].l] = q[i].k;
		}
		else
		{
			l = q[i].l;
			r = q[i].r;
			ans = 0;
			
			while (l <= r)
			{
				if (l % sqrtN == 0 && l + sqrtN - 1 <= r)
				{
					ans += sqrtN - getCnt(l / sqrtN, q[i].k);
					l += sqrtN;
				}
				else
				{
					if (a[l] > q[i].k) ans++;
					l++;
				}
			}
			cout << ans << "\n";
		}
	}
	return 0;
}