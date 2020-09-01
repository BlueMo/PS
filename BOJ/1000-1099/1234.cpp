// 1234: 크리스마스 트리
// fail1: fac 미리 안나눠줘서 overflow

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;

int N, cnt[3];
int fac[11] = {1, };
ll D[11][56][56];

ll DP(int n, int r, int g, int b)
{
	if (r < 0 || g < 0 || b < 0) return 0;
	ll &ret = D[n][r][g];
	if (ret != -1) return ret;
	if (!n) return 1;
	ret = 0;
	if (!(n%2))
	{
		int t = n/2;
		ret += DP(n-1, r-t, g-t, b) * (fac[n] / fac[t] / fac[t]);
		ret += DP(n-1, r, g-t, b-t) * (fac[n] / fac[t] / fac[t]);
		ret += DP(n-1, r-t, g, b-t) * (fac[n] / fac[t] / fac[t]);
	}
	if (!(n%3))
	{
		int t = n/3;
		ret += DP(n-1, r-t, g-t, b-t) * (fac[n] / fac[t] / fac[t] / fac[t]);
	}
	ret += DP(n-1, r-n, g, b) + DP(n-1, r, g-n, b) + DP(n-1, r, g, b-n);
	
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	memset(D, -1, sizeof(D));
	cin >> N;
	for (int i = 1; i <= N; ++i) fac[i] = fac[i-1] * i;
	for (int i = 0; i < 3; ++i)
		cin >> cnt[i];
	
	cout << DP(N, min(cnt[0], 55), min(cnt[1], 55), min(cnt[2], 55));
	return 0;
}