// 9177: 단어 섞기

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
string a, b, s;
int n, D[404][202];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int t = 1; t <= n; ++t)
	{
		cin >> a >> b >> s;
		memset(D, 0, sizeof(D));
		
		D[0][0] = 1;
		
		for (int i = 1; i <= s.size(); ++i)
		{
			if (i <= b.size() && s[i-1] == b[i-1]) D[i][0] = D[i-1][0];
			if (i <= a.size() && s[i-1] == a[i-1]) D[i][i] = D[i-1][i-1];
			
			for (int j = 1; j <= min(i-1, (int)a.size()); ++j)
			{
				if (s[i-1] == a[j-1] && D[i-1][j-1]) D[i][j] = 1;
				if (s[i-1] == b[i-j-1] && D[i-1][j]) D[i][j] = 1;
			}
		}
		
		cout << "Data set " << t << ": ";
		if (D[s.size()][a.size()]) cout << "yes\n";
		else cout << "no\n";
	}
	return 0;
}