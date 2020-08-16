// 1176: 섞기

#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int N, K, a[17];
long long D[1<<16][17];

long long dp(int now, int b)
{
	if (b == (1<<N)-1) return 1;
	long long &ret = D[b][now];
	if (ret != -1) return ret;
	
	ret = 0;
	if (now != N)
	{
		for (int i = 0; i < N; ++i)
		{
			if (b & (1<<i)) continue;
			if (abs(a[now] - a[i]) <= K) continue;
			ret += dp(i, b | (1<<i));
		}
	}
	else
	{
		for (int i = 0; i < N; ++i)
			ret += dp(i, b | (1<<i));
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i)
		cin >> a[i];
	
	memset(D, -1, sizeof(D));
	cout << dp(N, 0);
	return 0;
}