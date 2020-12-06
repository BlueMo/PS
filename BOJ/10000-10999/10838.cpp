// 10838: 트리

#include<bits/stdc++.h>
using namespace std;

int N, K, p[100002], w[100002], chk[100002], a, b, c, r, t, idx;
vector<int> color;

int lca(int u, int v)
{
	if (u == v) return u;
	
	idx++;
	while (1)
	{
		chk[u] = chk[v] = idx;
		u = p[u];
		v = p[v];
		
		if (u == v) return u;
		if (u && chk[u] == idx) return u;
		if (v && chk[v] == idx) return v;
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	color.reserve(100002);
	
	for (int i = 0; i < K; ++i)
	{
		cin >> r >> a >> b;
		
		if (r == 1)
		{
			cin >> c;
			t = lca(a, b);
			
			while (t != a)
			{
				w[a] = c;
				a = p[a];
			}
			while (t != b)
			{
				w[b] = c;
				b = p[b];
			}
		}
		else if (r == 2)
		{
			p[a] = b;
		}
		else
		{
			t = lca(a, b);
			while (t != a)
			{
				color.push_back(w[a]);
				a = p[a];
			}
			while (t != b)
			{
				color.push_back(w[b]);
				b = p[b];
			}
			sort(color.begin(), color.end());
			color.erase(unique(color.begin(), color.end()), color.end());
		
			cout << color.size() << "\n";
			color.clear();
		}
	}
	return 0;
}