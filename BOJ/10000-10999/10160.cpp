// 10160: 암호

#include<iostream>
#include<algorithm>
#define MOD 1000000009
using namespace std;
typedef long long ll;

int N, K;
ll D[1000001];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> K;
	
	D[0] = 1;
	for (int i = 1; i <= 5; ++i) D[i] = (D[i-1] * K) % MOD;
	D[5] -= 2;
	D[6] = K*D[5] - D[1]*2;
	for (int i = 7; i <= N; ++i)
		D[i] = (K*D[i-1] - D[i-5]*2 + D[i-7]) % MOD;
	
	cout << (D[N] + MOD) % MOD;
	return 0;
}