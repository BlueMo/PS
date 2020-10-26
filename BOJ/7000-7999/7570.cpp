// 7570: 줄 세우기

#include<iostream>
#include<algorithm>
using namespace std;

int N, a, b[1000001], ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		b[a] = b[a-1] + 1;
		ans = max(ans, b[a]);
	}
	
	cout << N - ans;
	return 0;
}