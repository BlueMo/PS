// 5626: 제단

#include<iostream>
#include<algorithm>
#include<cstring>
#define MOD 1000000007
using namespace std;

int N, a, max_h, k;
long long D[2][5002];
long long *p;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	max_h = ((N-1)>>1) + 1;
	
	D[0][1] = 1;
	for (int i = 1; i <= N; ++i, k = !k)
	{
		cin >> a;
		a++;
		
		if (a)
			D[!k][a] = (D[k][a-1] + D[k][a] + D[k][a+1]) % MOD;
		else
		{
			for (int j = 1; j <= i && j <= max_h; ++j)
				D[!k][j] = (D[k][j-1] + D[k][j] + D[k][j+1]) % MOD;
		}
		
		p = &D[k][0];
		memset(p, 0, sizeof(D)/2);
	}
	
	cout << D[k][1];
	return 0;
}