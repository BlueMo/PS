// 2631: 줄세우기

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N, a, idx;
vector<int> b;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;
	cin >> a;
	b.push_back(a);
	for (int i = 1; i < N; ++i)
	{
		cin >> a;
		idx = upper_bound(b.begin(), b.end(), a) - b.begin();
		if (idx == b.size()) b.push_back(a);
		else if (b[idx] > a) b[idx] = a;
	}
	cout << N - b.size();
	return 0;
}