// 12999: 화려한 마을3

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int N, Q, a[100001], l, r, v;
int cnt[200002], map[100001], max_cnt, ans[100001];
struct Q
{
	int l, r, idx;
	ll d;
	
	bool operator < (const Q &a) const { return d < a.d; }
}q[100001];

ll convHilbert(int x, int y, int pow, int rotate)
{
	if (!pow) return 0;
	pow--;

	int hpow = 1 << pow;
	int seg;
	if (x < hpow)
	{
		if (y < hpow) seg = 0;
		else seg = 3;
	}
	else
	{
		if (y < hpow) seg = 1;
		else seg = 2;
	}
	seg = (seg + rotate) & 3;
	int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll sq_size = ll(1) << (pow << 1);
	ll ans = seg * sq_size;
	ll add = convHilbert(nx, ny, pow, nrot);
	if (seg == 1 || seg == 2) ans += add;
	else ans += sq_size - add - 1;
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i)
	{
		cin >> a[i];
		a[i] += 100000;
	}
	for (int i = 0; i < Q; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].idx = i;
		q[i].d = convHilbert(q[i].l, q[i].r, 17, 0);
	}
	sort(q, q+Q);
	
	l = q[0].l;
	r = l - 1;
	
	for (int i = 0; i < Q; ++i)
	{
		while (l > q[i].l)
		{
			l--;
			v = a[l];
			if (cnt[v]) map[cnt[v]]--;
			cnt[v]++;
			map[cnt[v]]++;
			max_cnt = max(max_cnt, cnt[v]);
		}
		while (r < q[i].r)
		{
			r++;
			v = a[r];
			if (cnt[v]) map[cnt[v]]--;
			cnt[v]++;
			map[cnt[v]]++;
			max_cnt = max(max_cnt, cnt[v]);
		}
		while (l < q[i].l)
		{
			v = a[l];
			map[cnt[v]]--;
			if (!map[max_cnt]) max_cnt--;
			cnt[v]--;
			map[cnt[v]]++;
			l++;
		}
		while (r > q[i].r)
		{
			v = a[r];
			map[cnt[v]]--;
			if (!map[max_cnt]) max_cnt--;
			cnt[v]--;
			map[cnt[v]]++;
			r--;
		}
		ans[q[i].idx] = max_cnt;
	}
	
	for (int i = 0; i < Q; ++i)
		cout << ans[i] << "\n";
	return 0;
}