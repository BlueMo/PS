// 16979 수열과 쿼리 23

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;

int N, M, l, r;
int tree[100001], a[100001];
ll ans[100001], total_cnt;
vector<int> b;

struct Q
{
	int l, r, idx;
	ll d;
	
	bool operator < (const Q &a) const{ return d < a.d; }
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

int get_idx(int val)
{
	return lower_bound(b.begin(), b.end(), val) - b.begin() + 1;
}

void updateFwT(int idx, int is_push = 1)
{
	while (idx <= 100000)
	{
		tree[idx] += is_push;
		idx += idx & -idx;
	}
}

int getCnt(int idx)
{
	int cnt = 0;
	if (idx < 1) return 0;
	
	while (idx > 0)
	{
		cnt += tree[idx];
		idx -= idx & -idx;
	}
	return cnt;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		cin >> a[i];
		b.push_back(a[i]);
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	
	for (int i = 1; i <= N; ++i)
		a[i] = get_idx(a[i]);
	
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
		for (int j = l; j < q[i].l; ++j)
		{
			total_cnt -= getCnt(a[j]-1);
			updateFwT(a[j], -1);
		}
		for (int j = l-1; j >= q[i].l; --j)
		{
			total_cnt += getCnt(a[j]-1);
			updateFwT(a[j]);
		}
		for (int j = r+1; j <= q[i].r; ++j)
		{
			total_cnt += getCnt(100000) - getCnt(a[j]);
			updateFwT(a[j]);
		}
		for (int j = r; j > q[i].r; --j)
		{
			total_cnt -= getCnt(100000) - getCnt(a[j]);
			updateFwT(a[j], -1);
		}
		ans[q[i].idx] = total_cnt;
		l = q[i].l;
		r = q[i].r;
	}
	for (int i = 0; i < M; ++i)
		cout << ans[i] << "\n";
	return 0;
}
