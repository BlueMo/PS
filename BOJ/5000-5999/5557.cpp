// 5557: 1학년

#include<iostream>
#include<algorithm>
using namespace std;

int N, a, b;
long long D[101][21];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	cin >> a;
	
	D[0][a] = 1;
	for (int i = 1; i < N-1; ++i)
	{
		cin >> b;
		for (int j = 0; j <= 20; ++j)
		{
			if (D[i-1][j])
			{
				if (j + b <= 20) D[i][j+b] += D[i-1][j];
				if (j - b >= 0) D[i][j-b] += D[i-1][j];
			}
		}
		a = b;
	}
	cin >> a;
	
	cout << D[N-2][a];
	return 0;
}