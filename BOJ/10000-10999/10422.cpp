// 10422: 괄호

#include<iostream>
#include<algorithm>
#define MOD 1000000007
using namespace std;

int T, L;
int D[2501][2501];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	
	D[0][0] = 1;
	for (int i = 1; i <= 2500; ++i)
		for (int j = 0; j <= i; ++j)
			D[i][j] = (D[i-1][j] + D[i][j-1]) % MOD; 
	
	while (T--)
	{
		cin >> L;
		if (L & 1) cout << "0\n";
		else cout << D[L>>1][L>>1] << "\n";
	}
	return 0;
}