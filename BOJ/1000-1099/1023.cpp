// 1023: 괄호 문자열
// fail1: -1 출력 안함

#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

int N;
ll D[51][102], p, K;
bool flag=1;
string ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	K++;
	D[1][N+1] = 1;
	
	for (int i = 2; i <= N; ++i)
		for (int j = N; j <= N+i; ++j)
			D[i][j] = D[i-1][j+1] + D[i-1][j-1];
	
	if ((1LL << N) - D[N][N] < K)
	{
		cout << "-1";
		return 0;
	}
	int i = N-1, j = N+1;
	ll t = 1LL << (N-1);
	
	while (i >= 0)
	{
		p = t;
		if (flag) p -= D[i][j];

		if (K <= p)
		{
			i--;
			j++;
			t >>= 1;
			ans.push_back('(');
		}
		else if (K > p)
		{
			K -= p;
			i--;
			j--;
			if (j == N) flag = 0;
			t >>= 1;
			ans.push_back(')');
		}
	}	
	cout << ans;
	return 0;
}