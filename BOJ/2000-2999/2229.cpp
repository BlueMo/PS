// 2229: 조 짜기

#include<iostream>
#include<algorithm>
using namespace std;

int N, mn, mx;
int a[1002], D[1002];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
		cin >> a[i];
	
	for (int i = 1; i <= N; ++i)
	{
		mn = mx = a[i];
		for (int j = i-1; j >= 1; --j)
		{
			mx = max(mx, a[j]);
			mn = min(mn, a[j]);
			D[i] = max(D[i], D[j-1] + mx - mn);
		}
	}
	cout << D[N];
	return 0;
}