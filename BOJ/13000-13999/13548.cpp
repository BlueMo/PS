// 13548: 수열과 쿼리 6

#include<iostream>
#include<cmath>
#include<algorithm>
#define MAX(a,b) (((a)>(b))?(a):(b))
using namespace std;

int N, M, sz, l, r, max_cnt;
int a[100002], cnt[100001], map[100001], ans[100001];

struct Q
{
	int l, r, idx;
	
	bool operator < (const Q &a) const
	{
		if (l/sz != a.l/sz) return l/sz < a.l/sz;
		return r < a.r;
	}
}q[100001];

void push(int v)
{
	if (cnt[v]) map[cnt[v]]--;
	cnt[v]++;
	map[cnt[v]]++;
	max_cnt = MAX(max_cnt, cnt[v]);
}

void pop(int v)
{
	map[cnt[v]]--;
	if (!map[max_cnt]) max_cnt--;
	cnt[v]--;
	map[cnt[v]]++;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	sz = sqrt(N);					// bucket size
	for (int i = 1; i <= N; ++i)
		cin >> a[i];
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].idx = i;
	}
	sort(q, q+M);
	
	for (int i = 0; i < M; ++i)
	{
		for (int j = l; j < q[i].l; ++j) pop(a[j]);
		for (int j = l-1; j >= q[i].l; --j) push(a[j]);
		for (int j = r+1; j <= q[i].r; ++j) push(a[j]);
		for (int j = r; j > q[i].r; --j) pop(a[j]);
		ans[q[i].idx] = max_cnt;
		l = q[i].l;
		r = q[i].r;
	}
	for (int i = 0; i < M; ++i)
		cout << ans[i] << "\n";
	return 0;
}