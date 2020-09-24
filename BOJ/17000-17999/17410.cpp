// 17410: 수열과 쿼리 1.5

#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int N, M, a[100002], bs, bn, q, l, r, k, ans;
int tree[100][10002];

void updateFwT(int bN, int idx, int is_push=1)
{
	while (idx <= 10000)
	{
		tree[bN][idx] += is_push;
		idx += idx & -idx;
	}
}

int getCnt(int bN, int idx)
{
	int cnt = 0;
	
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
	for (int i = 0; i < N; ++i)
		cin >> a[i];
	
	//bs = sqrt(N);
	bs = sqrt(N*log2(N+1));
	bn = N / bs;
	for (int i = 0; i <= bn; ++i)
	{
		int e = min((i+1)*bs, N);
		for (int j = i*bs; j < e; ++j) updateFwT(i, a[j]);
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q;
		if (q == 1)
		{
			cin >> l >> k;
			l--;
			updateFwT(l/bs, a[l], -1);
			updateFwT(l/bs, k);
			a[l] = k;
		}
		else
		{
			cin >> l >> r >> k;
			l--;
			r--;
			ans = 0;
			
			while (l <= r)
			{
				if (l % bs == 0 && l + bs - 1 <= r)
				{
					ans += bs - getCnt(l/bs, k);
					l += bs;
				}
				else
				{
					if (a[l] > k) ans++;
					l++;
				}
			}
			cout << ans << "\n";
		}
	}
	return 0;
}