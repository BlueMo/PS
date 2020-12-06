// 13511: 트리와 쿼리 2

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int N, M, lgN, q, u, v, w;
int L[100001], D[100001][18];
ll W[100001];
vector<pii> G[100001];

void DFS(int x, int p, int l, ll w)
{
	L[x] = l;
	W[x] = w;
	
	for (auto &i : G[x])
	{
		if (p == i.first) continue;
		
		D[i.first][0] = x;
		DFS(i.first, x, l+1, w+i.second);
	}
}

void buildSpT()
{
	for (int j = 1; j <= lgN; ++j)
	{
		for (int i = 1; i <= N; ++i)
			D[i][j] = D[D[i][j-1]][j-1];
	}
}

int lca(int a, int b)
{
	if (L[a] < L[b]) swap(a, b);
	
	for (int i = 0, t = L[a] - L[b]; t; ++i, t >>= 1)
	{
		if (t & 1) a = D[a][i];
	}
	
	if (a == b) return a;
	
	for (int i = lgN; i >= 0; --i)
	{
		if (D[a][i] != D[b][i])
		{
			a = D[a][i];
			b = D[b][i];
		}
	}
	return D[a][0];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	lgN = log2(N);
	for (int i = 1; i < N; ++i)
	{
		cin >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	DFS(1, 0, 0, 0LL);
	buildSpT();
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q >> u >> v;
		
		if (q == 1)
			cout << W[u] + W[v] - 2*W[lca(u, v)] << "\n";
		else
		{
			cin >> w;
			
			w--;
			int t = lca(u, v), d = L[u] - L[t];
			
			if (d == w) cout << t << "\n";
			else
			{
				if (d < w)
				{
					w = L[v] - L[t] - w + d;
					swap(u, v);
				}
				
				for (int j = 0; w; ++j, w >>= 1)
				{
					if (w & 1) u = D[u][j];
				}
				cout << u << "\n";
			}
		}
	}
	return 0;
}