// 2624: 동전 바꿔주기

#include<iostream>
#include<algorithm>
using namespace std;

int T, K, p, n, D[10001];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> T >> K;
	
	D[0] = 1;
	for (int i = 0; i < K; ++i)
	{
		cin >> p >> n;
		for (int j = T - p; j >= 0; --j)
		{
			if (!D[j]) continue;
			for (int k = 1; k <= n; ++k)
			{
				if (j + k*p > T) break;
				D[j + k*p] += D[j];
			}
		}
	}
	
	cout << D[T];
	return 0;
}