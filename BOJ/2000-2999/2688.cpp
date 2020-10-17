// 2688: 줄어들지 않아

#include<iostream>
#include<algorithm>
using namespace std;

int T, n, a[1001], maxN;
long long ans, D[65][10];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		cin >> a[i];
		maxN = max(maxN, a[i]);
	}
	
	for (int i = 0; i < 10; ++i) D[1][i] = 1;
	for (int i = 2; i <= maxN; ++i)
	{
		for (int j = 0; j < 10; ++j)
			for (int k = 0; k <= j; ++k)
				D[i][j] += D[i-1][k];
	}
	
	for (int i = 0; i < T; ++i)
	{
		ans = 0;
		for (int j = 0; j < 10; ++j) ans += D[a[i]][j];
		cout << ans << "\n";
	}
	return 0;
}