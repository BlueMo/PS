// 13546: 수열과 쿼리 4

#include<iostream>
#include<algorithm>
#include<cmath>
#include<list>
#define sz 320
using namespace std;
typedef long long ll;

int N, M, K, l, r, d, t;//, sqrtN;
int a[100001], ans[100001], cnt[100200], bcnt[sz];
list<int> idx[100001];

struct Q
{
	int l, r, idx;
	ll d;
	
	bool operator < (const Q &a) const
	{
		//if (l/sqrtN != a.l/sqrtN) return l < a.l;
		//return r < a.r;
		return d < a.d;
	}
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
	
	cin >> N >> K;
	//sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i)
		cin >> a[i];
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].idx = i;
		q[i].d = convHilbert(q[i].l, q[i].r, 17, 0);
	}
	sort(q, q+M);
	
	l = q[0].l;
	r = l - 1;
	for (int i = 0; i < M; ++i)
	{
		while (l > q[i].l)
		{
			l--;
			t = a[l];
			if (!idx[t].empty())
			{
				d = idx[t].back() - idx[t].front();
				cnt[d]--;
				bcnt[d/sz]--;
			}
			idx[t].push_front(l);
			d = idx[t].back() - l;
			cnt[d]++;
			bcnt[d/sz]++;
		}
		while (r < q[i].r)
		{
			r++;
			t = a[r];
			if (!idx[t].empty())
			{
				d = idx[t].back() - idx[t].front();
				cnt[d]--;
				bcnt[d/sz]--;
			}
			idx[t].push_back(r);
			d = r - idx[t].front();
			cnt[d]++;
			bcnt[d/sz]++;
		}
		while (l < q[i].l)
		{
			t = a[l];
			d = idx[t].back() - idx[t].front();
			cnt[d]--;
			bcnt[d/sz]--;
			idx[t].pop_front();
			if (!idx[t].empty())
			{
				d = idx[t].back() - idx[t].front();
				cnt[d]++;
				bcnt[d/sz]++;
			}
			l++;
		}
		while (r > q[i].r)
		{
			t = a[r];
			d = idx[t].back() - idx[t].front();
			cnt[d]--;
			bcnt[d/sz]--;
			idx[t].pop_back();
			if (!idx[t].empty())
			{
				d = idx[t].back() - idx[t].front();
				cnt[d]++;
				bcnt[d/sz]++;
			}
			r--;
		}
		for (int j = 312; j >= 0; --j)
		{
			if (!bcnt[j]) continue;
			for (int k = 319; k >= 0; --k)
			{
				if (cnt[j*sz + k])
				{
					ans[q[i].idx] = j*sz + k; 
					break;
				}
			}
			break;
		}
	}
	
	for (int i = 0; i < M; ++i)
		cout << ans[i] << "\n";

	return 0;
}