// 1796: 신기한 키보드

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

string s;

int getAns(int p, char idx)
{
	if (idx > 'z') return 0;
	
	int l, r;
	l = r = -1;
	for (int i = 0; i < p; ++i)
	{
		if (s[i] == idx)
		{
			l = i;
			break;
		}
	}
	for (int i = s.size()-1; i > p; --i)
	{
		if (s[i] == idx)
		{
			r = i;
			break;
		}
	}
	if (l == -1 && r == -1) return getAns(p, idx+1);
	
	int a, b;
	a = b = 0x7fffffff;
	if (l != -1)
	{
		a = getAns(l, idx+1) + p - l;
		if (r != -1) a += 2 * (r - p);
	}
	if (r != -1)
	{
		b = getAns(r, idx+1) + r - p;
		if (l != -1) b += 2 * (p - l);
	}
	
	return min(a, b);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> s;
	
	cout << getAns(0, 'a') + s.size();
	return 0;
}