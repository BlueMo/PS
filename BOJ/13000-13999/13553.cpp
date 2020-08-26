// 13553: 수열과 쿼리 8
// fail1: segtree TLE -> 나중에 fenwick 하고 속도 차이 시험해보자
// fail2: fenwick 구현 실수

#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int N, M, K, l, r, sz;
int a[100001], tree[100001];
ll ans[100001], total_cnt;

struct Q
{
	int l, r, idx;
	
	bool operator < (const Q &a) const
	{
		if (l/sz != a.l/sz) return l/sz < a.l/sz;
		return r < a.r;
	}
}q[100001];

void updateFwT(int idx, int is_push=1)
{
	while (idx <= 100000)
	{
		tree[idx] += is_push;
		idx += (idx & -idx);
	}
}

int getCnt(int idx)
{
	int cnt = 0;
	if (idx < 1) return 0;
	if (idx > 100000) idx = 100000;
	
	while (idx > 0)
	{
		cnt += tree[idx];
		idx -= (idx & -idx);
	}
	return cnt;				// exclude A_i
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	sz = sqrt(N);
	for (int i = 1; i <= N; ++i)
		cin >> a[i];
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].idx = i;
	}
	sort(q, q+M);
	
	l = q[0].l;
	r = l - 1;
	for (int i = 0; i < M; ++i)
	{
		for (int j = l; j < q[i].l; ++j)
		{
			updateFwT(a[j], -1);
			total_cnt -= getCnt(a[j]+K) - getCnt(a[j]-K-1);
		}
		for (int j = l-1; j >= q[i].l; --j)
		{
			total_cnt += getCnt(a[j]+K) - getCnt(a[j]-K-1);
			updateFwT(a[j]);
		}
		for (int j = r+1; j <= q[i].r; ++j)
		{
			total_cnt += getCnt(a[j]+K) - getCnt(a[j]-K-1);
			updateFwT(a[j]);
		}
		for (int j = r; j > q[i].r; --j)
		{
			updateFwT(a[j], -1);
			total_cnt -= getCnt(a[j]+K) - getCnt(a[j]-K-1);
		}
		ans[q[i].idx] = total_cnt;
		l = q[i].l;
		r = q[i].r;
	}
	for (int i = 0; i < M; ++i)
		cout << ans[i] << "\n";
	return 0;
}