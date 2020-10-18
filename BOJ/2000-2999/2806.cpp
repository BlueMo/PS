// 2806: DNA 발견

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

int N, D[1000002][2];
vector<int> p;
string s;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> s;
	
	for (int i = 1; i < s.size(); ++i)
	{
		if (s[i] != s[i-1]) p.push_back(i);
	}
	p.push_back(N);
	
	if (s[0] == 'A') D[0][1] = 1;
	else D[0][0] = 1;
	
	for (int i = 0; i < p.size()-1; ++i)
	{
		if (s[p[i]] == 'B')
		{
			D[i+1][0] = min(D[i][0] + p[i+1] - p[i], D[i][1] + 1);
			D[i+1][1] = min(D[i][1], D[i][0] + 1);
		}
		else
		{
			D[i+1][1] = min(D[i][1] + p[i+1] - p[i], D[i][0] + 1);
			D[i+1][0] = min(D[i][0], D[i][1] + 1);
		}
	}
	
	cout << D[p.size()-1][0];
	return 0;
}