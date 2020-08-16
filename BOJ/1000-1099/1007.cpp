// 1007: 벡터 매칭

#include<iostream>
#include<cmath>
#define MIN(a,b) (((a)>(b))?(b):(a))
using namespace std;

struct P
{
	int x, y;
}p[21];

int T, N;
double sum_x, sum_y;


double comb(int n, int k, double sx, double sy)
{
	if (k == N/2)
	{
		sx = 2*sx - sum_x;
		sy = 2*sy - sum_y;
		return sqrt(sx*sx + sy*sy);
	}
	if (n == N) return 0x7fffffff;
	double a, b;
	a = comb(n+1, k+1, sx+p[n].x, sy+p[n].y);
	if (n-k+1 >= N/2) return a;
	b = comb(n+1, k, sx, sy);
	return MIN(a, b);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	cout << fixed;
	cout.precision(7);
	while (T--)
	{
		sum_x = sum_y = 0;
		cin >> N;
		for (int i = 0; i < N; ++i)
		{
			cin >> p[i].y >> p[i].x;
			sum_x += p[i].x;
			sum_y += p[i].y;
		}
		cout << comb(0, 0, 0, 0) << "\n";
	}
	return 0;
}