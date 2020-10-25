// 5582: 공통 부분 문자열

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

string a, b;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> a+1;
	cin >> b+1;
	for (int i = 1; i <= strlen(a+1); ++i)
	{
		for (int j = 1; j <= strlen(b+1); ++j)
		{
			if (a[i] == b[j])
			{
				D[i][j] = D[i-1][j-1] + 1;
				ans = max(ans, D[i][j]);
			}
		}
	}
	
	cout << ans;
	return 0;
}