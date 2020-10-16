// 2296: 건물짓기
// fail1~2: ans = MAX(D[N-1], D2[N-1]) 로 해버림... N번째 건물을 무조건 포함하는 경우

#include<iostream>
#include<algorithm>
using namespace std;

struct P
{
	int x, y, c;
	
	bool operator< (const P &a) const { return x < a.x; }
}p[1001];
int N, D[1001], D2[1001], ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> p[i].x >> p[i].y >> p[i].c;
	sort(p, p+N);
	
	for (int i = 0; i < N; ++i)
	{
		D[i] = D2[i] = p[i].c;
		for (int j = 0; j < i; ++j)
		{
			if (p[i].y > p[j].y && D[i] < D[j] + p[i].c)
				D[i] = D[j] + p[i].c;
			if (p[i].y < p[j].y && D2[i] < D2[j] + p[i].c)
				D2[i] = D2[j] + p[i].c;
		}
		ans = max(ans, max(D[i], D2[i]));
	}
	cout << ans;
	return 0;
}