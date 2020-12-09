// 2150: Strongly Connected Component
// Kosaraju

#include<bits/stdc++.h>
using namespace std;

int V, E, a, b, idx[10001];
bool chk[10001];
vector<int> adj[10001], radj[10001], scc[10001];
stack<int> st;

void DFS(int x)
{
	chk[x] = 1;
	for (auto &i : adj[x])
	{
		if (!chk[i]) DFS(i);
	}
	st.push(x);
}

void rDFS(int x, int n)
{
	chk[x] = 0;
	scc[n].push_back(x);
	for (auto &i : radj[x])
	{
		if (chk[i]) rDFS(i, n);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> V >> E;
	for (int i = 0; i < E; ++i)
	{
		cin >> a >> b;
		adj[a].push_back(b);
		radj[b].push_back(a);
	}
	
	for (int i = 1; i <= V; ++i)
	{
		if (!chk[i]) DFS(i);
	}
	
	a = 1;
	while (!st.empty())
	{
		int h = st.top();
		st.pop();
		if (!chk[h]) continue;
		rDFS(h, a);
		sort(scc[a].begin(), scc[a].end());
		idx[scc[a][0]] = a;
		a++;
	}
	
	cout << a-1 << "\n";
	for (int i = 1; i <= V; ++i)
	{
		if (!idx[i]) continue;
		for (auto &j : scc[idx[i]])
			cout << j << " ";
		cout << "-1\n";
	}
	return 0;
}