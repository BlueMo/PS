// 6549: 히스토그램에서 가장 큰 직사각형
// Union-find

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int n, p[100002], h[100002], a[100002], r[100002];
ll ans;

bool cmp(const int &a, const int &b){ return h[a] > h[b]; }

int findParent(int s)
{
	if (p[s] == s) return s;
	return p[s] = findParent(p[s]);
}

void unionSet(int a, int b)
{
	a = findParent(a), b = findParent(b);
	if (a == b) return;
	r[a] += r[b];
	p[b] = a;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while (1)
	{
		cin >> n;
		if (!n) break;
		
		r[n+1] = 0;
		ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			cin >> h[i];
			p[i] = a[i] = i;
			r[i] = 0;
		}
		sort(a+1, a+n+1, cmp);
		
		for (int i = 1; i <= n; ++i)
		{
			int t = a[i];
			r[t] = 1;
			if (r[t-1]) unionSet(t, t-1);
			if (r[t+1]) unionSet(t, t+1);
			
			ans = max(ans, (ll)h[t] * r[t]);
		}
		cout << ans << "\n";
	}
	return 0;
}