// 3176: 도로 네트워크

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;


int N, lgN, K, a, b, c;
int L[100001], D[200001][18], mn[200001][18], mx[200001][18];
vector<pii> G[100001];

void DFS(int x, int p, int l)
{
	L[x] = l;
	
	for (auto &i : G[x])
	{
		if (i.first == p) continue;
		D[i.first][0] = x;
		mn[i.first][0] = mx[i.first][0] = i.second;
		DFS(i.first, x, l+1);
	}
}

void buildSpT()
{
	for (int j = 1; j <= lgN; ++j)
	{
		for (int i = 1; i <= N; ++i)
		{
			int p = D[i][j-1];
			D[i][j] = D[p][j-1];
			mn[i][j] = min(mn[i][j-1], mn[p][j-1]);
			mx[i][j] = max(mx[i][j-1], mx[p][j-1]);
		}
	}
}

pii LCA(int u, int v)
{
	int rmn = 1000001, rmx = 0;
	if (L[u] < L[v]) swap(u, v);
	
	int t = L[u] - L[v];
	for (int i = 0; t; ++i, t >>= 1)
	{
		if (t & 1)
		{
			rmn = min(rmn, mn[u][i]);
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
				rmn = min({rmn, mn[u][i], mn[v][i]});
				rmx = max({rmx, mx[u][i], mx[v][i]});
				u = D[u][i];
				v = D[v][i];
			}
		}	
		rmn = min({rmn, mn[u][0], mn[v][0]});
		rmx = max({rmx, mx[u][0], mx[v][0]});
	}
	
	return {rmn, rmx};
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	lgN = log2(N);
	for (int i = 0; i < N-1; ++i)
	{
		cin >> a >> b >> c;
		G[a].push_back({b, c});
		G[b].push_back({a, c});
	}
	DFS(1, 0, 0);
	buildSpT();
	
	cin >> K;
	pii ans;
	for (int i = 0; i < K; ++i)
	{
		cin >> a >> b;
		ans = LCA(a, b);
		cout << ans.first << " " << ans.second << "\n";
	}
	
	return 0;
}