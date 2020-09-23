// 6549: 히스토그램에서 가장 큰 직사각형
// sweeping, stack
// fail1: ans 초기화 안해줌

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int n, h[100003], s[100003], en;
ll ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	while (1)
	{
		cin >> n;
		if (!n) break;
		ans = en = h[n+1] = 0;
		for (int i = 1; i <= n; ++i)
			cin >> h[i];
	
		s[++en] = 1;
		for (int i = 2; i <= n+1; ++i)
		{
			while (en > 0 && h[s[en]] >= h[i])
			{
				ans = max(ans, 1LL * (i - s[en-1] - 1) * h[s[en]]);
				en--;
			}
			s[++en] = i;
		}
		cout << ans << "\n";
	}
	return 0;
}