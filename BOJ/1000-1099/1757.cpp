// 1757: 달려달려

#include<iostream>
#include<algorithm>
using namespace std;

int N, M, a, D[10001][501];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		cin >> a;
		D[i][0] = D[i-1][0];
		for (int j = 0; j <= min(i-1, M); ++j)
		{
			D[i][0] = max(D[i][0], D[i-j][j]);
			D[i][1] = max(D[i][1], D[i-j-1][j] + a);
		}	
		for (int j = 2; j <= M; ++j)
			D[i][j] = D[i-1][j-1] + a;
	}
	
	cout << D[N][0];
	return 0;
}