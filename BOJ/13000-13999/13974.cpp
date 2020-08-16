// 13974: 파일 합치기 2

#include<iostream>
#define MIN(a,b) (((a)<(b))?(a):(b))
using namespace std;

int L[5002];
int T, N, i, j, k, a, tmp;
int D[5002][5002], minK[5002][5002];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	
	while (T--)
	{
		cin >> N;

		for (i = 1; i <= N; i++)
		{
			cin >> a;
			L[i] = L[i-1] + a;
			D[i-1][i] = 0;	// for Knuth Optimization: shift i
			minK[i-1][i] = i;
		}
		for (j = 2; j <= N; j++)
		{
			for (i = j-2; i >= 0; i--)
			{
				D[i][j] = 0x7fffffff;
				
				for (k = minK[i][j-1]; k <= minK[i+1][j]; k++)
				{
					tmp = D[i][k] + D[k][j] + L[j] - L[i];
					if (D[i][j] > tmp)
					{
						D[i][j] = tmp;
						minK[i][j] = k;
					}
				}
			}
		}
		cout << D[0][N] << "\n";
	}
	return 0;
}