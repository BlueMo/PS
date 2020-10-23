// 14504: 수열과 쿼리 18

#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int N, sqrtN, M, q, l, r, k, a[100002], b[100002], ans, t, e, p;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	sqrtN = sqrt(N);
	for (int i = 0; i < N; ++i)
		cin >> a[i];
	memcpy(b, a, sizeof(a));
	
	for (int i = 0; i <= sqrtN; ++i)
	{
		e = min((i+1)*sqrtN, N);
		sort(a + i*sqrtN, a + e);
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q;
		if (q == 1)
		{
			cin >> l >> r >> k;
			ans = 0, l--, r--;
			while (l <= r)
			{
				if (l % sqrtN == 0 && l + sqrtN - 1 <= r)
				{
					t = l / sqrtN;
					ans += (a + (t+1)*sqrtN) - upper_bound(a + t*sqrtN, a + (t+1)*sqrtN, k);
					l += sqrtN;
				}
				else
				{
					ans += b[l] > k ? 1 : 0;
					l++;
				}
			}
			cout << ans << "\n";
		}
		else
		{
			cin >> l >> k;
			l--;
			t = l / sqrtN;
			e = min((t+1)*sqrtN, N);
			p = lower_bound(a + t*sqrtN, a + e, b[l]) - a;
			a[p] = k;
	
			for (int j = p; a[j-1] > a[j] && j > t*sqrtN; --j)
				swap(a[j], a[j-1]);
			for (int j = p; a[j+1] < a[j] && j < e-1; ++j)
				swap(a[j], a[j+1]);
			b[l] = k;
			
		}
	}
	return 0;
}