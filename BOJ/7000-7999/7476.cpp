// 7476: 최대 공통 증가 수열
// -1을 참조하고 있었네 ㅁㄴㅇㄹ

#include<iostream>
#include<algorithm>
using namespace std;

int N, M, a[502], b[502], p, cnt, ml, aa, bb;
int D[502][502], v[502][502], ans[502];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
		cin >> a[i];
	cin >> M;
	for (int i = 1; i <= M; ++i)
		cin >> b[i];
	
	for (int i = 1; i <= N; ++i)
	{
		cnt = p = 0;
		for (int j = 1; j <= M; ++j)
		{
			D[i][j] = D[i-1][j];
			v[i][j] = -1;
			if (a[i] == b[j])
			{
				D[i][j] = cnt + 1;
				v[i][j] = p;
			}
			else if (a[i] > b[j] && D[i-1][j] > cnt)
			{
				cnt = D[i-1][j];
				p = j;
			}
			
			if (D[i][j] > ml)
			{
				ml = D[i][j];
				aa = i;
				bb = j;
			}
		}
	}
	cout << ml << "\n";
	for (int i = aa, j = ml; i >= 1; --i)
	{
		if (v[i][bb] != -1)
		{
			ans[--j] = b[bb];
			bb = v[i][bb];
			if (!bb) break;
		}
	}
	for (int i = 0; i < ml; ++i)
		cout << ans[i] << " ";
	return 0;
}