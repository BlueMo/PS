// 2666: 벽장문의 이동

#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int N, M, a[21], x, y;
int D[21][21][21];

int getAns(int idx, int x, int y)
{
	if (idx == M) return 0;
	
	int &ret = D[idx][x][y];
	if (ret != -1) return ret;
	
	return ret = min(getAns(idx+1, min(x, a[idx]), max(x, a[idx])) + abs(y - a[idx]),
					 getAns(idx+1, min(y, a[idx]), max(y, a[idx])) + abs(x - a[idx]));
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> x >> y >> M;
	if (x > y) swap(x, y);
	for (int i = 0; i < M; ++i)
		cin >> a[i];
	memset(D, -1, sizeof(D));
	
	cout << getAns(0, x, y);
	return 0;
}