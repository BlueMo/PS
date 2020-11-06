// 15896: &+ +&

#include<iostream>
#include<algorithm>
#include<cstring>
#define MOD 1999
#define MAX 0x20000000
using namespace std;
typedef long long ll;

int N;
ll a[1000001], b[1000001], mina[2], minb[2], maxa[2], maxb[2], ans;
ll bit_flag, bit_flag2;
int cnt[29], cnt2[29], t;
bool flag;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> a[i];
		for (int j = 0; j < 30; ++j)
			cnt[j] += (a[i] & (1LL<<j)) ? 1 : 0;
	}
	
	for (int j = 0; j < 30; ++j) cnt[j] = cnt[j] % MOD;
	
	for (int i = 0; i < N; ++i)
	{
		cin >> b[i];
		for (int j = 0; j < 30; ++j)
		{
			if (b[i] & (1LL<<j))
			{
				cnt2[j]++;
				ans = (ans + ((1LL<<j)%MOD * cnt[j])) % MOD;
			}
		}
	}
	cout << ans << " ";
	ans = 0;
	
	for (int i = 0; i < 30; ++i)
	{
		mina[0] = mina[1] = minb[0] = minb[1] = MAX;
		maxa[0] = maxa[1] = maxb[0] = maxb[1] = 0;
		flag = 1;
		bit_flag = 1LL << i;
		bit_flag2 = bit_flag - 1;
		
		for (int j = 0; j < N; ++j)
		{
			t = (a[j] & bit_flag) ? 1 : 0;
			mina[t] = min(mina[t], (a[j] & bit_flag2));
			maxa[t] = max(maxa[t], (a[j] & bit_flag2));
			t = (b[j] & bit_flag) ? 1 : 0;
			minb[t] = min(minb[t], (b[j] & bit_flag2));
			maxb[t] = max(maxb[t], (b[j] & bit_flag2));
		}
		
		if ( (mina[0] != MAX && minb[0] != MAX) && !((mina[0] + minb[0]) & bit_flag) )
			flag = 0;
		else if ( (mina[1] != MAX && minb[1] != MAX) && !((mina[1] + minb[1]) & bit_flag) )
			flag = 0;
		else if ( (mina[0] != MAX && minb[1] != MAX) && ((maxa[0] + maxb[1]) & bit_flag) )
			flag = 0;
		else if ( (mina[1] != MAX && minb[0] != MAX) && ((maxa[1] + maxb[0]) & bit_flag) )
			flag = 0;
		
		ans += flag << i;
	}
	cout << ans;
	return 0;
}