// 15480: LCA와 쿼리

#include<bits/stdc++.h>
using namespace std;

int N, lgN, M, r, u, v, idx;
int I[100001], E[200001], L[200001], SpT[200001][20]; 
vector<int> adj[100001];

void DFS(int x, int p, int l)
{
	I[x] = idx;
	SpT[idx][0] = idx;
	E[idx] = x;
	L[idx++] = l;
	
	for (auto &i : adj[x])
	{
		if (i == p) continue;
		
		DFS(i, x, l+1);
		SpT[idx][0] = idx;
		E[idx] = x;
		L[idx++] = l;
	}
}

void buildSpT()
{
	lgN = log2(idx);
	for (int j = 1; j <= lgN; ++j)
	{
		for (int i = 0; i+(1<<j)-1 < idx; ++i)
			SpT[i][j] = L[SpT[i][j-1]] < L[SpT[i+(1<<(j-1))][j-1]] ? 
						SpT[i][j-1] : SpT[i+(1<<(j-1))][j-1];
	}
}

int lca(int u, int v)
{
	u = I[u], v = I[v];
	if (u > v) swap(u, v);
	
	int k = log2(v-u+1);
	
	return L[SpT[u][k]] < L[SpT[v-(1<<k)+1][k]] ? E[SpT[u][k]] : E[SpT[v-(1<<k)+1][k]];
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
	DFS(1, 0, 0);
	buildSpT();
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> r >> u >> v;
		
		int a = lca(u, v);
		int b = lca(r, u);
		int c = lca(r, v);
		
		if (a == b)
			cout << c << "\n";
		else if (a == c)
			cout << b << "\n";
		else
			cout << a << "\n";
	}
	return 0;
}