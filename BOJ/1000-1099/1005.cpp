#include<iostream>
#include<vector>
#include<queue>
#define MAX(a, b) (((a)>(b))?(a):(b))
using namespace std;
int T, N, K, X, Y, W, h;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	
	while(T--)
	{
		cin >> N >> K;
		
		vector<int> D(N), p(N), TimeTable(N);
		vector<int> b[N];
		queue<int> Q;
		for (int i = 0; i < N; i++)
			cin >> D[i];
		for (int i = 0; i < K; i++)
		{
			cin >> X >> Y;
			p[Y-1]++;
			b[X-1].push_back(Y-1);
		}
		
		cin >> W;
		
		for (int i = 0; i < N; i++)
		{
			if (!p[i])
			{
				Q.push(i);
				TimeTable[i] = D[i];
			}
		}
		
		while(!Q.empty())
		{
			h = Q.front();
			Q.pop();
			
			for (int i : b[h])
			{
				p[i]--;
				TimeTable[i] = MAX(TimeTable[i], TimeTable[h] + D[i]);
				if (!p[i])
				{
					Q.push(i);
					p[i]--;		//check
				}
			}
		}
		cout << TimeTable[W-1] << "\n";
	}
	return 0;
}