// 3793: Common Subsequence

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int D[202][202];
string a, b;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	while (cin >> a >> b)
	{
		memset(D, 0, sizeof(D));
		
		for (int i = 1; i <= a.size(); ++i)
		{
			for (int j = 1; j <= b.size(); ++j)
			{
				if (a[i-1] == b[j-1]) D[i][j] = D[i-1][j-1] + 1;
				else D[i][j] = max(D[i-1][j], D[i][j-1]);
			}
		}
		cout << D[a.size()][b.size()] << "\n";
	}
	return 0;
}
