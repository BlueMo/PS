// 1256: 사전

#include<iostream>
#include<algorithm>
using namespace std;

int N, M, K;
int c[201][201];

void DF(int n, int m)
{
	if (!n)
	{
		for (int i = m; i > 0; --i)
			cout << "z";
		return;
	}
	else if (!m)
	{
		for (int i = n; i > 0; --i)
			cout << "a";
		return;
	}
	else if (c[n+m-1][m] >= K)
	{
		cout << "a";
		DF(n-1, m);
	}
	else
	{
		cout << "z";
		K -= c[n+m-1][m];
		DF(n, m-1);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M >> K;
	c[0][0] = 1;
	for (int i = 1; i <= N+M; ++i)
	{
		c[i][0] = 1;
		for (int j = 1; j < i; ++j) c[i][j] = min(1000000000, c[i-1][j-1] + c[i-1][j]);
		c[i][i] = 1;
	}
	
	if (K > c[N+M][M])
		cout << "-1";
	else
		DF(N, M);
	return 0;
}