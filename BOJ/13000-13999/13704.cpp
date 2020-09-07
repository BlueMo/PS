// 13704: 수열과 쿼리 11

#include<iostream>
#include<cmath>
#include<algorithm>
#include<utility>
using namespace std;
typedef long long ll;

int N, M, K, l, r, a[100001];
ll total_cnt, cnt[1050000], ans[100001];

struct Q
{
	int l, r, idx;
	ll d;
	
	bool operator < (const Q &a) const 
	{
		return d < a.d;
	}
}q[100001];

ll convHilbert(int x, int y, int pow, int rotate)
{
	if (!pow) return 0;
	int hpow = 1 << (pow - 1);
	int seg = (x < hpow) ? ((y < hpow)?0:3) : ((y < hpow)?1:2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x^hpow), ny = y & (y^hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSquareSize = (ll)1 << (2*pow - 2);
	ll ans = seg * subSquareSize;
	ll add = convHilbert(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	for (int i = 1; i <= N; ++i)
	{
		cin >> a[i];
		a[i] ^= a[i-1];
	}
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].l--;
		q[i].idx = i;
		q[i].d = convHilbert(q[i].l, q[i].r, 17, 0);
	}
	sort(q, q+M);
	
	l = q[0].l;
	r = l - 1;
	for (int i = 0; i < M; ++i)
	{
		while (l < q[i].l)
		{
			cnt[a[l]]--;
			total_cnt -= cnt[K^a[l]];
			l++;
		}
		while (l > q[i].l)
		{
			l--;
			total_cnt += cnt[K^a[l]];
			cnt[a[l]]++;
		}
		while (r < q[i].r)
		{
			r++;
			total_cnt += cnt[K^a[r]];
			cnt[a[r]]++;
		}
		while (r > q[i].r)
		{
			cnt[a[r]]--;
			total_cnt -= cnt[K^a[r]];
			r--;
		}
		ans[q[i].idx] = total_cnt;
	}
	for (int i = 0; i < M; ++i)
		cout << ans[i] << "\n";
	
	return 0;
}