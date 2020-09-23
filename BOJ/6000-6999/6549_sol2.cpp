// 6549: 히스토그램에서 가장 큰 직사각형
// Divide & Conquer

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int n, h[100001];

ll getS(int l, int r)
{
	if (l == r) return (ll)h[l];
	int mid = (l+r)>>1;
	int s = mid, e = mid+1;
	int min_h = min(h[s], h[e]);
	ll ret = min_h << 1;
	
	while (l < s || e < r)
	{
		if (l == s)
		{
			while (e < r)
			{
				min_h = min(min_h, h[++e]);
				ret = max(ret, 1LL * (e-s+1) * min_h);
			}
			break;
		}
		else if (e == r)
		{
			while (l < s)
			{
				min_h = min(min_h, h[--s]);
				ret = max(ret, 1LL * (e-s+1) * min_h);
			}
			break;
		}
		
		if (h[s-1] >= h[e+1])
		{
			min_h = min(min_h, h[--s]);
			ret = max(ret, 1LL * (e-s+1) * min_h);
		}
		else
		{
			min_h = min(min_h, h[++e]);
			ret = max(ret, 1LL * (e-s+1) * min_h);
		}
	}
	
	return max(ret, max(getS(l, mid), getS(mid+1, r)));
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while (1)
	{
		cin >> n;
		if (!n) break;
		for (int i = 0; i < n; ++i)
			cin >> h[i];
		cout << getS(0, n-1) << "\n";
	}
	return 0;
}