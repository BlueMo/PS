// 11266: 단절점

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int V, E, u, v, t, num, root, ans;
int idx[10002];
bool cutVertex[10002];
vector<int> G[10002];

int dfs(int u)
{
	int cnt = 0, ret;
	ret = idx[u] = num++;
	for (int v : G[u])
	{
		if (idx[v] == -1)
		{
			cnt++;
			t = dfs(v);
			
			if (root != u && t >= idx[u]) cutVertex[u] = 1;
			ret = min(ret, t);
		}
		else ret = min(ret, idx[v]);
	}
	if (root == u && cnt >= 2) cutVertex[u] = 1;
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> V >> E;
	memset(idx, -1, sizeof(idx));
	
	for (int i = 0; i < E; ++i)
	{
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	for (int i = 1; i <= V; ++i)
	{
		if (idx[i] == -1)
		{
			num = 0;
			root = i;
			dfs(i);
		}
		if (cutVertex[i]) ans++;
	}
	cout << ans << "\n";
	for (int i = 1; i <= V; ++i)
	{
		if (cutVertex[i]) cout << i << " ";
	}
	return 0;
}