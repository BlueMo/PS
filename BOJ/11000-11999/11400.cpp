// 11400: 단절선
/* 단절점끼리 연결한 선분은 무조건 단절선?
 * : No. 1-2-3-4-5
 *         |___|
 * 이 경우 2, 4는 단절점인데 2-4는 단절선이 아님
 */

#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int, int> ii;

int V, E, u, v, num;
int idx[100002];
vector<int> G[100002];
vector<ii> cutEdge;

int dfs(int u, int p)
{
	int t, ret;
	ret = idx[u] = num++;

	for (int v : G[u])
	{
		if (v == p) continue;
		if (idx[v] == -1)
		{
			t = dfs(v, u);
			
			if (t > idx[u]) cutEdge.push_back({min(u, v), max(u, v)});
			ret = min(ret, t);
		}
		else ret = min(ret, idx[v]);
	}
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
			dfs(i, 0);
		}
	}
	sort(cutEdge.begin(), cutEdge.end());
	cout << cutEdge.size() << "\n";
	for (ii i : cutEdge)
		cout << i.first << " " << i.second << "\n";
	return 0;
}