// 3257: 발코딩

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int D[151][151];
string a, b, s, ans;

int getAns(int idx, int x, int y)
{
	if (idx == s.size()) return 1;
	
	int &ret = D[x][y];
	if (ret != -1) return ret;
	
	ret = 0;
	if (x < a.size() && s[idx] == a[x])
		ret = getAns(idx+1, x+1, y);
	if (ret)
	{
		ans += "1";
		return ret;
	}
	if (y < b.size() && s[idx] == b[y])
		ret = getAns(idx+1, x, y+1);
	if (ret) ans += "2";
	
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> a >> b >> s;
	memset(D, -1, sizeof(D));
	
	getAns(0, 0, 0);
	for (int i = ans.size()-1; i >= 0; --i)
		cout << ans[i];
	return 0;
}