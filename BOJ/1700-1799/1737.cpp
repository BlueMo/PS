// 1737: Pibonacci

#include<iostream>
using namespace std;
typedef long long ll;

int N, t;
ll D[1002][330];
const ll MOD = 1e18;
const double PI = 3.14159;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	D[0][0] = 1;
	for (int i = 1; i <= N; ++i)
	{
		t = (int)(i / PI);
		D[i][t] = 1;
		for (int j = t-1; j >= 0; --j)
			D[i][j] = (0LL + D[i-1][j] + D[i][j+1]) % MOD;
	}
	
	cout << D[N][0];
	return 0;
}