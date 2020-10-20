// 4095: 최대 정사각형

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int D[1002][1002], a[1002][1002];
int N, M, ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	while (cin >> N >> M)
	{
		if (!N && !M) break;
		memset(D, 0, sizeof(D));
		ans = 0;
		
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= M; ++j)
				cin >> a[i][j];
		
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= M; ++j)
			{
				if (!a[i][j]) continue;
				D[i][j] = min(D[i-1][j-1], min(D[i-1][j], D[i][j-1])) + 1;
				ans = max(ans, D[i][j]);
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
