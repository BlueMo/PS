// 5721: 사탕 줍기 대회

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int N, M;
int a[100002], Dx[100002], Dy[100002];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while (cin >> N >> M)
	{
		if (!N && !M) break;
		
		for (int i = 1; i <= N; ++i)
		{
			cin >> Dx[1];
			for (int j = 2; j <= M; ++j)
			{
				cin >> a[j];
				Dx[j] = max(Dx[j-2] + a[j], Dx[j-1]);
			}
			if (i == 1) Dy[i] = Dx[M];
			else Dy[i] = max(Dy[i-2] + Dx[M], Dy[i-1]);
		}
		
		cout << Dy[N] << "\n";
	}
	return 0;
}