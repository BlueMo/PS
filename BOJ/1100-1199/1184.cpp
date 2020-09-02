// 1184: 귀농

#include<iostream>
using namespace std;

int N, a[52][52], cnt, t = 2500000;
int S[5000000];

int calcS(int y1, int x1, int y2, int x2)
{
	return a[y2][x2] - a[y1][x2] - a[y2][x1] + a[y1][x1];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cin >> a[i][j];
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
		}
	}
	
	for (int i = 1; i < N; ++i)
	{
		for (int j = 1; j < N; ++j)
		{
			for (int y = 0; y < i; ++y)
				for (int x = 0; x < j; ++x)
					S[t + calcS(y, x, i, j)]++;
			
			for (int y = i+1; y <= N; ++y)
				for (int x = j+1; x <= N; ++x)
					cnt += S[t + calcS(i, j, y ,x)];
			
			for (int y = 0; y < i; ++y)
				for (int x = 0; x < j; ++x)
					S[t + calcS(y, x, i, j)]--;
			
			for (int y = 0; y < i; ++y)
				for (int x = j+1; x <= N; ++x)
					S[t + calcS(y, j, i, x)]++;
			
			for (int y = i+1; y <= N; ++y)
				for (int x = 0; x < j; ++x)
					cnt += S[t + calcS(y, j, i, x)];
			
			for (int y = 0; y < i; ++y)
				for (int x = j+1; x <= N; ++x)
					S[t + calcS(y, j, i, x)]--;
		}
	}
	
	cout << cnt;
}