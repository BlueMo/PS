// 5569: 출근 경로

#include<iostream>
#include<algorithm>
#define MOD 100000
using namespace std;

int w, h;
int D[101][101][2][2];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> w >> h;
	
	D[1][1][1][1] = 1;
	D[1][1][0][0] = 1;
	
	for (int i = 1; i <= h; ++i)
	{
		for (int j = 1; j <= w; ++j)
		{
			if (i > 1) 
			{
				D[i][j][0][0] = (D[i-1][j][0][0] + D[i-1][j][0][1]) % MOD;
				if (j > 1) D[i][j][0][1] = D[i-1][j][1][1];
			}
			if (j > 1)
			{
				D[i][j][1][1] = (D[i][j-1][1][1] + D[i][j-1][1][0]) % MOD;
				if (i > 1) D[i][j][1][0] = D[i][j-1][0][0];
			}
		}
	}
	
	cout << (D[h][w][0][0] + D[h][w][0][1] + D[h][w][1][0] + D[h][w][1][1]) % MOD;
	return 0;
}