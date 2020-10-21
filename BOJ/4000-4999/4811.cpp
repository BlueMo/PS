// 4811: 알약

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int N;
long long D[31];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	D[0] = D[1] = 1;
	for (int i = 2; i <= 30; ++i)
	{
		D[i] += D[i-1];
		for (int j = 0; j < i-1; ++j)
		D[i] += D[i-j-1] * D[j];
	}
	
	while (cin >> N)
	{
		if (!N) break;
		cout << D[N] << endl;
	}
	return 0;
}