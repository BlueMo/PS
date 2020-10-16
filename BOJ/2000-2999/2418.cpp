// 2418: 단어격자

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;

int H, W, L;
int dy[8] = {-1,-1,-1,0,0,1,1,1}, dx[8] = {-1,0,1,-1,1,-1,0,1};
char map[202][202], s[202];
ll D[202][202][101], ans;

ll getAns(int y, int x, int idx)
{
	if (!y || !x || y > H || x > W) return 0LL;
	if (idx == L) return 1LL;
	
	ll &ret = D[y][x][idx];
	if (ret != -1) return ret;
	
	ret = 0LL;
	for (int i = 0; i < 8; ++i)
	{
		int ny = y + dy[i], nx = x + dx[i];
		if (map[ny][nx] == s[idx+1])
			ret += getAns(ny, nx, idx+1);
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> H >> W >> L;
	L--;
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			cin >> map[i][j];
	cin >> s;
	memset(D, -1, sizeof(D));
	
	for (int i = 1; i <= H; ++i)
	{
		for (int j = 1; j <= W; ++j)
		{
			if (s[0] == map[i][j]) ans += getAns(i, j, 0);
		}
	}
	
	cout << ans;
	return 0;
}