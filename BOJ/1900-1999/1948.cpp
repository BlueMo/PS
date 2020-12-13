// 1948: 임계경로
// fail1: 중복 방문

#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int N, M, u, v, w, p[10001], maxw[10001], h, ans;
bool chk[10001];
vector<pii> adj[10001], radj[10001];
queue<int> q, q2;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		radj[v].push_back({u, w});
		p[v]++;
	}
	cin >> u >> v;
	
	q.push(u);
	while (!q.empty())
	{
		h = q.front();
		q.pop();
		
		for (auto &i : adj[h])
		{
			p[i.first]--;
			maxw[i.first] = max(maxw[i.first], maxw[h]+i.second);
			if (!p[i.first]) q.push(i.first);
		}
	}
	cout << maxw[v] << "\n";
	
	q2.push(v);
	while (!q2.empty())
	{
		h = q2.front();
		q2.pop();
		
		for (auto &i : radj[h])
		{
			if (maxw[h] == maxw[i.first] + i.second)
			{
				ans++;
				if (!chk[i.first])
				{
					q2.push(i.first);
					chk[i.first] = 1;
				}
			}
		}
	}
	
	cout << ans;
	return 0;
}