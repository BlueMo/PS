// 8012: 한동이는 영업사원!

#include<bits/stdc++.h>
using namespace std;

int N, lgN, a, b, M, ans;
int L[30001];
int D[30001][16];
vector<int> G[30001];

void DFS(int x, int p, int l)
{
	L[x] = l;
	
	for (auto &i : G[x])
	{
		if (i == p) continue;
		D[i][0] = x;
		DFS(i, x, l+1);
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

int LCA(int u, int v)
{
	if (L[u] < L[v]) swap(u, v);
	int t = L[u] - L[v];
	
	for (int i = 0; t; ++i, t >>= 1)
	{
		if (t & 1) u = D[u][i];
	}
	
	if (u == v) return u;
	
	for (int i = lgN; i >= 0; --i)
	{
		if (D[u][i] != D[v][i])
		{
			u = D[u][i];
			v = D[v][i];
		}
	}
	return D[u][0];
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	lgN = log2(N);
	
	for (int i = 1; i < N; ++i)
	{
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	DFS(1, 0, 0);
	buildSpT();
	
	cin >> M >> a;
	for (int i = 1; i < M; ++i)
	{
		cin >> b;
		ans += L[a] + L[b] - 2*L[LCA(a, b)];
		a = b;
	}
	cout << ans;
	return 0;
}