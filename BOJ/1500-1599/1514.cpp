// 1514: 자물쇠
// fail: 칸 돌리는걸 한번만 시행했었는데, 여러번 시행하는게 최적인 경우가 있음.
// ex) 872 -> 947
// 72 -> 49(2칸 동시, 1회) -> 47(1칸만, 2회) 

#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int N, D[101][10][10], ans, t;
int st[101], en[101], d1, d2, d3;
char c;

int move(int s, int e)
{
	if (s > e) swap(s, e);
	return (min(e - s, s - e + 10)+2)/3;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> c;
		st[i] = c - '0';
	}
	for (int i = 0; i < N; ++i)
	{
		cin >> c;
		en[i] = c - '0';
	}
	
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			d1 = st[1] - i;
			d2 = st[0] - j;
			if (d1 < 0) d1 += 10;
			if (d2 < 0) d2 += 10;
			
			d3 = move(d1, d2);
			d1 = move(0, d1);
			d2 = move(0, d2);
			
			D[1][i][j] = d1 + d2;
			if (d1 < d2) D[1][i][j] = min(D[1][i][j], d1 + d3);
			else D[1][i][j] = min(D[1][i][j], d2 + d3);
		}
	}
	
	for (int i = 2; i < N; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			for (int k = 0; k < 10; ++k)
			{
				D[i][j][k] = 0x7fffffff;
				for (int l = 0; l < 10; ++l)
				{
					for (int m = 0; m < 10; ++m)
					{
						d1 = st[i] - j;
						d2 = l - k;
						d3 = m - en[i-2];
						if (d1 < 0) d1 += 10;
						if (d2 < 0) d2 += 10;
						if (d3 < 0) d3 += 10;
						
						t = D[i-1][l][m];
						if (d3)
						{
							t += move(0, d3);
							d1 -= d3;
							d2 -= d3;
							if (d1 < 0) d1 += 10;
							if (d2 < 0) d2 += 10;
						}
						if (d2)
						{
							t += move(0, d2);
							d1 -= d2;
							if (d1 < 0) d1 += 10;
						}
						if (d1) t += move(0, d1);
						
						D[i][j][k] = min(D[i][j][k], t);
					}
				}
			}
		}
	}
	
	cout << D[N-1][en[N-1]][en[N-2]];
	return 0;
}