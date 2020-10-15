// 2225: 합분해

#include<iostream>
#include<algorithm>
using namespace std;

int N, K, t;
int D[201][2];
const int MOD = 1e9;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	
	for (int i = 0; i <= N; ++i) D[i][1] = 1;
	
	t = 1;
	for (int k = 2; k <= K; ++k)
	{
		t = !t;
		for (int i = 0; i <= N; ++i)
		{
			D[i][t] = 0;
			for (int j = 0; j <= i; ++j)
			{
				D[i][t] += D[j][!t];
				if (D[i][t] >= MOD) D[i][t] -= MOD;
			}
		}
	}
	
	cout << D[N][t];
	return 0;
}