// 17731: Historical Research
// fail1: for (i ~ sqrtN) -> i ~ sqrtN+1

#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;

int N, Q, l, r, x[100002], cnt[100002], a[100002], sqrtN;
vector<int> x_idx;
ll ans[100002], sub_ans, t;

struct Q
{
	int l, r, idx;
	
	bool operator < (const Q &a) const
	{
		if (l/sqrtN != a.l/sqrtN) return l < a.l;
		return r < a.r;
	}
}q[100002];

int getIdx(int val){ return lower_bound(x_idx.begin(), x_idx.end(), val) - x_idx.begin(); }

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> Q;
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i)
	{
		cin >> x[i];
		x_idx.push_back(x[i]);
	}
	sort(x_idx.begin(), x_idx.end());
	x_idx.erase(unique(x_idx.begin(), x_idx.end()), x_idx.end());
	for (int i = 1; i <= N; ++i)
		a[i] = getIdx(x[i]);
	for (int i = 0; i < Q; ++i)
	{
		cin >> q[i].l >> q[i].r;
		q[i].idx = i;
	}
	q[Q].l = q[Q].r = N+1;			// for문 exit
	sort(q, q + Q);
	
	int j = 0, e;
	for (int i = 0; i <= sqrtN + 1; ++i)
	{
		e = min((i+1)*sqrtN, N+1);
		for (int k = i*sqrtN; k <= N; ++k) cnt[a[k]] = 0;
		while (q[j].l < e && q[j].r < e)
		{
			sub_ans = 0;
			for (int k = q[j].l; k <= q[j].r; ++k)
			{
				cnt[a[k]]++;
				sub_ans = max(sub_ans, (ll)cnt[a[k]]*x[k]);
			}
			ans[q[j].idx] = sub_ans;
			for (int k = q[j].l; k <= q[j].r; ++k) cnt[a[k]] = 0;
			j++;
		}
		sub_ans = 0;
		l = e;
		r = e - 1;
		while (q[j].l < e)
		{
			while (q[j].r > r)
			{
				r++;
				cnt[a[r]]++;
				sub_ans = max(sub_ans, (ll)cnt[a[r]]*x[r]);
			}
			t = sub_ans;
			while (q[j].l < l)
			{
				l--;
				cnt[a[l]]++;
				sub_ans = max(sub_ans, (ll)cnt[a[l]]*x[l]); 
			}
			ans[q[j].idx] = sub_ans;
			sub_ans = t;
			while (l < e)
			{
				cnt[a[l]]--;
				l++;
			}
			j++;
		}
	}
	
	for (int i = 0; i < Q; ++i)
		cout << ans[i] << "\n";
	return 0;
}