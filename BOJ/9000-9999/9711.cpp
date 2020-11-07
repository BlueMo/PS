// 9711: 피보나치

#include<iostream>
#include<algorithm>
using namespace std;

int T, P, Q, i;
long long D[2];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	for (int j = 1; j <= T; ++j)
	{
		cin >> P >> Q;
		P--;
		i = 0;
		D[0] = 0;
		D[1] = 1 % Q;
		
		for (; P; i=!i, --P)
			D[i] = (D[i] + D[!i]) % Q;
		
		cout << "Case #" << j << ": " << D[!i] << "\n";
	}
	return 0;
}