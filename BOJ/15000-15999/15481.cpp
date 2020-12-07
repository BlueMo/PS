// 15481: 그래프와 MST

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

struct E
{
	int u, v, w;
	
	bool operator < (const E &a) const { return w < a.w; }
} t, G[200001], G2[200001];

int N, M, lgN, u, v, w, p[200001], L[200001];
int D[200001][20], mx[200001][20];
ll sum;
vector<pii> adj[200001];

int findParent(int s)
{
	if (p[s] == s) return s;
	return p[s] = findParent(p[s]);
}

void unionSet(int x, int y, int c)
{
	x = findParent(x);
	y = findParent(y);
	if (x == y) return;
	
	adj[y].push_back({x, c});
	adj[x].push_back({y, c});
	sum += (ll)c;
	p[y] = x;
}

void DFS(int x, int p, int l)
{
	L[x] = l;
	
	for (auto &i : adj[x])
	{
		if (i.first == p) continue;
		
		D[i.first][0] = x;
		mx[i.first][0] = i.second;
		DFS(i.first, x, l+1);
	}
}

void buildSpT()
{
	lgN = log2(N);
	
	for (int j = 1; j <= lgN; ++j)
	{
		for (int i = 1; i <= N; ++i)
		{
			int par = D[i][j-1];
			D[i][j] = D[par][j-1];
			mx[i][j] = max(mx[i][j-1], mx[par][j-1]);
		}
	}
}

int lca(int u, int v)
{
	int rmx = 0;
	if (L[u] < L[v]) swap(u, v);
	
	int t = L[u] - L[v];
	
	for (int i = 0; t; ++i, t >>= 1)
	{
		if (t & 1)
		{
			rmx = max(rmx, mx[u][i]);
			u = D[u][i];
		}
	}
	
	if (u != v)
	{
		for (int i = lgN; i >= 0; --i)
		{
			if (D[u][i] != D[v][i])
			{
				rmx = max({rmx, mx[u][i], mx[v][i]});
				u = D[u][i];
				v = D[v][i];
			}
		}
		rmx = max({rmx, mx[u][0], mx[v][0]}); 
	}
	
	return rmx;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) p[i] = i;
	
	for (int i = 0; i < M; ++i)
	{
		cin >> t.u >> t.v >> t.w;
		G2[i] = G[i] = t;
	}
	sort(G, G+M);
	
	for (int i = 0; i < M; ++i) unionSet(G[i].u, G[i].v, G[i].w);
	
	DFS(1, 0, 0);
	buildSpT();
	
	for (int i = 0; i < M; ++i)
	{
		int t = lca(G2[i].u, G2[i].v);
		cout << sum - t + G2[i].w << "\n";
	}
	
	return 0;
}