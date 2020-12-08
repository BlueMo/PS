// 1626: 두 번째로 작은 스패닝 트리

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct Edge
{
	int u, v, w;
	
	bool operator < (const Edge &a) const { return w < a.w; }
}G[200001];

int V, lgV, E, sum, a, b, c, p[50001], ans = 0x7fffffff, cnt;
int D[50001][20], L[50001];
pii mx[50001][20];
bool chk[200001];
vector<pii> adj[50001];

int findParent(int s)
{
	if (s == p[s]) return s;
	return p[s] = findParent(p[s]);
}

bool unionSet(int u, int v, int w)
{
	int uu = findParent(u);
	int vv = findParent(v);
	if (uu == vv) return 0;
	
	sum += w;
	cnt++;
	adj[u].push_back({v, w});
	adj[v].push_back({u, w});
	p[vv] = uu;
	return 1;
}

void DFS(int x, int p, int l)
{
	L[x] = l;
	
	for (auto &i : adj[x])
	{
		if (i.first == p) continue;
		D[i.first][0] = x;
		mx[i.first][0] = {i.second, -1};
		DFS(i.first, x, l+1);
	}
}

pii cmp_mx(pii a, pii b)
{
	vector<int> tmp(5);
	tmp[0] = a.first, tmp[1] = a.second, tmp[2] = b.first, tmp[3] = b.second, tmp[4] = -1;
	sort(tmp.begin(), tmp.end(), greater<int>());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	
	return {tmp[0], tmp[1]};
}

void buildSpT()
{
	for (int j = 1; j <= lgV; ++j)
	{
		for (int i = 1; i <= V; ++i)
		{
			int par = D[i][j-1];
			D[i][j] = D[par][j-1];
			mx[i][j] = cmp_mx(mx[i][j-1], mx[par][j-1]);
		}
	}
}

int lca(int u, int v, int w)
{
	pii rmax = {-1, -1};
	
	if (L[u] < L[v]) swap(u, v);
	int t = L[u] - L[v];
	
	for (int i = 0; t; ++i, t >>= 1)
	{
		if (t & 1)
		{
			rmax = cmp_mx(rmax, mx[u][i]);
			u = D[u][i];
		}
	}
	
	if (u != v)
	{
		for (int i = lgV; i >= 0; --i)
		{
			if (D[u][i] != D[v][i])
			{
				rmax = cmp_mx(rmax, cmp_mx(mx[u][i], mx[v][i]));
				u = D[u][i];
				v = D[v][i];
			}
		}
		rmax = cmp_mx(rmax, cmp_mx(mx[u][0], mx[v][0]));
	}
	
	return w != rmax.first ? rmax.first : rmax.second;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> V >> E;
	lgV = log2(V);
	
	for (int i = 0; i < V; ++i) p[i] = i;
	for (int i = 0; i < E; ++i)
	{
		cin >> G[i].u >> G[i].v >> G[i].w;
	}
	sort(G, G+E);
	
	for (int i = 0; i < E; ++i)
		if (unionSet(G[i].u, G[i].v, G[i].w)) chk[i] = 1;
	
	if (cnt != V-1)
	{
		cout << "-1";
		return 0;
	}
	
	DFS(1, 0, 0);
	buildSpT();
	
	for (int i = 0; i < E; ++i)
	{
		if (chk[i]) continue;
		int t = lca(G[i].u, G[i].v, G[i].w);
		if (t == -1) continue;
		ans = min(ans, sum - t + G[i].w);
	}
	
	if (ans != 0x7fffffff) cout << ans;
	else cout << "-1";
	
	return 0;
}