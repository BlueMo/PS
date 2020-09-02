// 1209: 단조수열 만들기

#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;

int N, a[2001], a2[2001];
ll D[2001][2001], D2[2001][2001];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		cin >> a[i];
		a2[i] = a[i];
	}
	sort(a2+1, a2+N+1);
	
	for (int i = 1; i <= N; ++i)
	{
		D[i][0] = D2[i][0] = 1e13;
		for (int j = 1; j <= N; ++j)
		{
			D[i][j] = min(D[i][j-1], D[i-1][j] + abs(a[i] - a2[j]));
			D2[i][j] = min(D2[i][j-1], D2[i-1][j] + abs(a[i] - a2[N-j+1]));
		}
	}
	
	cout << min(D[N][N], D2[N][N]);
	return 0;
}