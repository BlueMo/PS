// 8012: 한동이는 영업사원!

#include<bits/stdc++.h>
using namespace std;

int N, lg, a, b, M, ans, idx;
int L[60001], E[60001], I[30001];
int SpT[60001][17];
vector<int> G[30001];

void DFS(int x, int p, int l)
{
	I[x] = idx;
	SpT[idx][0] = idx;
	L[idx] = l;
	E[idx++] = x;
	
	for (auto &i : G[x])
	{
		if (i == p) continue;
		DFS(i, x, l+1);
		L[idx] = l;
		SpT[idx][0] = idx;
		E[idx++] = x;
	}
}

void buildSpT()
{
	lg = log2(idx);
	for (int j = 1; j <= lg; ++j)
	{
		for (int i = 0; i+(1<<j)-1 < idx; ++i)
		{
			SpT[i][j] = L[SpT[i][j-1]] < L[SpT[i+(1<<(j-1))][j-1]] ? SpT[i][j-1] : SpT[i+(1<<(j-1))][j-1];
		}
	}
}

int LCA(int u, int v)
{
	u = I[u], v = I[v];
	if (u > v) swap(u, v);
	
	int k = log2(v-u+1);
	
	return min(L[SpT[u][k]], L[SpT[v-(1<<k)+1][k]]);
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	
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
		ans += L[I[a]] + L[I[b]] - 2*LCA(a, b);
		a = b;
	}
	cout << ans;
	return 0;
}