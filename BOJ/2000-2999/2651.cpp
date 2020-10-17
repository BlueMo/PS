// 2651: 자동차경주대회
// fail1: 비용이 0x7fffffff 일 경우, 갱신이 안됨
// fail~: 설마 정비소를 방문하지 않을 때 답이 0\n0 ??

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N, L, t, a[102], c[102], D[102], v[102];
vector<int> p;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> L >> N;
	for (int i = 0; i <= N; ++i)
		cin >> a[i];
	for (int i = 1; i <= N; ++i)
		cin >> c[i];
	
	for (int i = 1; i <= N+1; ++i)
	{
		D[i] = 0x7fffffff;
		t = 0;
		for (int j = i-1; j >= 0; --j)
		{
			t += a[j];
			if (t > L) break;
			if (D[i] >= D[j] + c[j])
			{
				D[i] = D[j] + c[j];
				v[i] = j;
			}
		}
	}
	cout << D[N+1] << "\n";
	
	if (D[N+1])
	{
		for (int i = N+1; i; i = v[i])
			p.push_back(v[i]);
		cout << p.size()-1 << "\n";
		for (int i = p.size()-2; i >= 0; --i)
			cout << p[i] << " ";
	}
	else cout << "0";
	return 0;
}