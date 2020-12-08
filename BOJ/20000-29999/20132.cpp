// 20132: Parity Constraint Minimum Spanning Tree

#include<bits/stdc++.h>
#define LL_MAX 0x7FFFFFFFFFFFFFFFLL
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

struct Edge
{
	int u, v;
	ll w;
	bool chk = 0;
	bool operator < (const Edge &a) const { return w < a.w; }
}G[300001];
int N, M, lgN, p[100001], cnt;
int L[100001], D[100001][20], even[100001][20], odd[100001][20];
bool flag;
ll sum, ans = LL_MAX;
vector<pii> adj[100001];

int findParent(int s)
{
	return p[s] == s ? s : (p[s] = findParent(p[s]));
}

bool unionSet(int u, int v, int w)
{
	int uu = findParent(u), vv = findParent(v);
	if (uu == vv) return 0;
	cnt++;
	sum += w;
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
		if (i.second & 1) odd[i.first][0] = i.second;
		else even[i.first][0] = i.second;
		DFS(i.first, x, l+1);
	}
}

void buildSpT()
{
	for (int j = 1; j <= lgN; ++j)
	{
		for (int i = 1; i <= N; ++i)
		{
			int par = D[i][j-1];
			D[i][j] = D[par][j-1];
			even[i][j] = max(even[i][j-1], even[par][j-1]);
			odd[i][j] = max(odd[i][j-1], odd[par][j-1]);
		}
	}
}

int lca(int u, int v, ll w)
{
	bool is_odd = w & 1;
	int rmax = 0;
	
	if (L[u] < L[v]) swap(u, v);
	int t = L[u] - L[v];
	for (int i = 0; t; ++i, t >>= 1)
	{
		if (t & 1)
		{
			if (is_odd) rmax = max(rmax, even[u][i]);
			else rmax = max(rmax, odd[u][i]);
			u = D[u][i];
		}
	}
	
	if (u != v)
	{
		for (int i = lgN; i >= 0; --i)
		{
			if (D[u][i] != D[v][i])
			{
				if (is_odd) rmax = max({rmax, even[u][i], even[v][i]});
				else rmax = max({rmax, odd[u][i], odd[v][i]});
				u = D[u][i], v = D[v][i];
			}
		}
		if (is_odd) rmax = max({rmax, even[u][0], even[v][0]});
		else rmax = max({rmax, odd[u][0], odd[v][0]});
	}
	
	return rmax;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	lgN = log2(N);
	for (int i = 1; i <= N; ++i) p[i] = i;
	for (int i = 0; i < M; ++i)
		cin >> G[i].u >> G[i].v >> G[i].w;
	sort(G, G+M);
	
	for (int i = 0; i < M; ++i)
	{
		if (unionSet(G[i].u, G[i].v, G[i].w)) G[i].chk = 1;
	}
	
	if (cnt != N-1)
	{
		cout << "-1 -1";
		return 0;
	}
	
	if (sum & 1) flag = 1;
	DFS(1, 0, 0);
	buildSpT();
	
	for (int i = 0; i < M; ++i)
	{
		if (G[i].chk) continue;
		int t = lca(G[i].u, G[i].v, G[i].w);
		if (!t) continue;
		ans = min(ans, sum - t + G[i].w);
	}
	
	if (flag)
	{
		cout << sum << " ";
		if (ans != LL_MAX) cout << ans;
		else cout << "-1";
	}
	else
	{
		if (ans != LL_MAX) cout << ans;
		else cout << "-1";
		cout << " " << sum;
	}
	
	return 0;
}