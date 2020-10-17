// 2758: 로또

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int T, maxn, maxm;
vector<int> n, m;
long long D[11][2001], ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	n.reserve(T);
	m.reserve(T);
	for (int i = 0; i < T; ++i)
	{
		cin >> n[i] >> m[i];
		maxn = max(maxn, n[i]);
		maxm = max(maxm, m[i]);
	}
	
	for (int i = 1; i <= maxm; ++i) D[1][i] = 1;
	for (int i = 2; i <= maxn; ++i)
		for (int j = i; j <= maxm; ++j)
			for (int k = 1; k <= j>>1; ++k)
				D[i][j] += D[i-1][k];
	
	for (int i = 0; i < T; ++i)
	{
		ans = 0;
		for (int j = n[i]; j <= m[i]; ++j) ans += D[n[i]][j];
		cout << ans << "\n";
	}
	return 0;
}