// 2533: 사회망 서비스(SNS)

#include<bits/stdc++.h>
using namespace std;

int N, u, v;
int D[1000001][2];
vector<int> adj[1000001];

int DFS(int x, int p, bool a)
{
	int &ret = D[x][a];
	
	ret = 0;
	for (auto &i : adj[x])
	{
		if (i == p) continue;
		int t1 = D[i][0] == -1 ? DFS(i, x, 0) : D[i][0];
		int t2 = D[i][1] == -1 ? DFS(i, x, 1) : D[i][1];
		
		if (!a) ret += t2;
		else ret += min(t1, t2);
	}
	
	if (a) ret++;

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i < N; ++i)
	{
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	memset(D, -1, sizeof(D));
	cout << min(DFS(1, 0, 0), DFS(1, 0, 1));
	return 0;
}