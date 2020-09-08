// 8462: 배열의 힘
// fail1: 연산할 때 int 범위 초과

#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;

int n, t, l, r;
int a[100001], cnt[1000001];
ll ans[100001], sub_ans;

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
	
	cin >> n >> t;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 0; i < t; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].idx = i;
		q[i].d = convHilbert(q[i].l, q[i].r, 17, 0);
	}
	sort(q, q+t);
	
	l = q[0].l;
	r = l - 1;
	for (int i = 0; i < t; ++i)
	{
		while (l > q[i].l)
		{
			l--;
			sub_ans += (ll)(2*cnt[a[l]] + 1) * a[l];
			cnt[a[l]]++;
		}
		while (r < q[i].r)
		{
			r++;
			sub_ans += (ll)(2*cnt[a[r]] + 1) * a[r];
			cnt[a[r]]++;
		}
		while (l < q[i].l)
		{
			sub_ans -= (ll)(2*cnt[a[l]] - 1) * a[l];
			cnt[a[l]]--;
			l++;
		}
		while (r > q[i].r)
		{
			sub_ans -= (ll)(2*cnt[a[r]] - 1) * a[r];
			cnt[a[r]]--;
			r--;
		}
		ans[q[i].idx] = sub_ans;
	}
	
	for (int i = 0; i < t; ++i)
		cout << ans[i] << "\n";
	return 0;
}