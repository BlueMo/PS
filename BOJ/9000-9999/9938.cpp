// 9938: 방 청소
// fail1: p[]를 N까지만 초기화시켜줌

#include<iostream>
#include<algorithm>
using namespace std;

int N, L, p[300001], a, b;

int findParent(int s)
{
	if (s == -1) return -1;
	if (s == p[s]) return s;
	return p[s] = findParent(p[s]);
}
bool merge(int u, int v)
{
	int pu = findParent(u);
	int pv = findParent(v);
	if (pu == u) p[u] = (pu != pv) ? v : -1;
	else if (pv == v) p[v] = (pu != pv) ? u : -1;
	else if (pu != -1) p[pu] = (pu != pv) ? pv : -1;
	else if (pv != -1) p[pv] = (pu != pv) ? pu : -1;
	else return 0;

	return 1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> L;
	for (int i = 1; i <= L; ++i) p[i] = i;
	
	for (int i = 1; i <= N; ++i)
	{
		cin >> a >> b;
		if (merge(a, b)) cout << "LADICA\n";
		else cout << "SMECE\n";
	}
	return 0;
}