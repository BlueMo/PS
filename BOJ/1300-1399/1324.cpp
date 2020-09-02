// 1324: 젠장
// fail1: 구현 실수 a[i]>b[j]를 a[i]>a[j]라고 씀

#include<iostream>
#include<algorithm>
using namespace std;

int N, a[1001], b[1001], D[1001], cnt;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> a[i];
	for (int i = 0; i < N; ++i)
		cin >> b[i];
	
	for (int i = 0; i < N; ++i)
	{
		cnt = 0;
		for (int j = 0; j < N; ++j)
		{
			if (a[i] == b[j]) D[j] = max(cnt+1, D[j]);
			else if (a[i] > b[j]) cnt = max(cnt, D[j]);
		}
	}
	
	cnt = 0;
	for (int i = 0; i < N; ++i)
		cnt = max(cnt, D[i]);
	
	cout << cnt;
	return 0;
}