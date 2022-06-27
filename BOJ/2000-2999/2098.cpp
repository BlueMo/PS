#include<iostream>
#define INF 0x7fffffff
#define MIN(a,b) (((a)>(b))?(b):(a))
using namespace std;

int N, w[20][20], D[20][1<<16], en;

int tsp(int v, int b)
{
	if (b == en)
	{
		if (w[v][0]) return w[v][0];
		else return D[v][b] = -1;
	}
	
	if (D[v][b]) return D[v][b];
	
	int c = INF;
	for (int i = 1; i < N; ++i)
	{
		if (b & (1<<i)) continue;
		
		if (w[v][i])
		{
			int t = tsp(i, b | (1<<i));
			if (t != -1)
				c = MIN(c, tsp(i, b | (1<<i)) + w[v][i]);
		}
	}
	if (c != INF)
		return D[v][b] = c;
	else
		return D[v][b] = -1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> w[i][j];

	en = (1<<N) - 1;
	cout << tsp(0, 1);
	return 0;
}