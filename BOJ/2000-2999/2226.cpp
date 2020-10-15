// 2226: 이진수

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int N, carry = 0;
vector<int> ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	
	ans.push_back(0);
	for (int i = 2; i <= N; ++i)
	{
		carry = 0;
		for (int &j : ans)
		{
			carry += j<<1;
			j = carry % 10;
			carry /= 10;
		}
		if (carry) ans.push_back(carry);
		
		if (i & 1)
		{
			int k = 0;
			ans[k]--;
			while (ans[k] < 0)
			{
				ans[k] += 10;
				ans[++k]--;
			}
		}
		else
		{
			int k = 0;
			ans[k]++;
			while (ans[k] > 9)
			{
				ans[k] -= 10;
				ans[++k]++;
			}
		}
	}
	
	for (int i = ans.size()-1; i >= 0; --i)
		cout << ans[i];
	return 0;
}