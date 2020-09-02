// 1720: 타일 코드

#include<iostream>
using namespace std;

int N, D[31];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	D[0] = D[1] = 1;
	D[2] = 3;
	
	for (int i = 3; i <= N; ++i)
		D[i] = 2*D[i-2] + D[i-1];
	
	if (N%2)
		cout << D[N] - D[N/2]*D[N/2-1]*2 - D[N/2]*(D[N/2]-1)/2;
	else
		cout << D[N] - (D[N/2]-1)*D[N/2]/2 - (D[N/2-1]-1)*D[N/2-1];
	return 0;
}