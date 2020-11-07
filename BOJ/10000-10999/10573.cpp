// 10573: 증가하는 수

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int T;
long long D[82][10], ans;
bool flag;
string s;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	for (int i = 0; i < 10; ++i) D[0][i] = 1;
	for (int i = 1; i < 81; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			for (int k = j; k < 10; ++k) 
				D[i][j] += D[i-1][k];
		}
	}
	while (T--)
	{
		flag = 0;
		cin >> s;
		for (int i = 1; i < s.size(); ++i)
		{
			if (s[i] < s[i-1])
			{
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			cout << "-1\n";
			continue;
		}
		
		ans = D[s.size()][0];
		
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i]-'0' != 9)
				ans -= D[s.size()-i][s[i]-'0'+1];
		}
		cout << ans-1 << "\n";
	}
	return 0;
}