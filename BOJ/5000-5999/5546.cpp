// 5546: 파스타

#include<iostream>
#include<algorithm>
#define MOD 10000
using namespace std;

int N, K, a, b, c[101];
int D[101][3][3], ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < K; ++i)
	{
		cin >> a >> b;
		c[a-1] = b;
	}
	
	if (c[0])
		D[0][c[0]-1][c[0]%3] = 1;
	else
		D[0][0][1] = D[0][1][2] = D[0][2][0] = 1;
	
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (c[i] && c[i]-1 != j) continue;
			for (int k = 0; k < 3; ++k)
			{
				if (j != k) D[i][j][k] += D[i-1][k][k];
				D[i][j][k] += D[i-1][k][(k+1)%3] + D[i-1][k][(k+2)%3];
				D[i][j][k] %= MOD;
			}
		}
	}
	
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ans = (ans + D[N-1][i][j]) % MOD;
	
	cout << ans;
	return 0;
}