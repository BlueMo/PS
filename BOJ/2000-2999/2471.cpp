// 2471: 모빌 이진수

#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<unordered_map>
#include<string>
using namespace std;

string s, h, a, b, tmp;
int K, len, t;
priority_queue< string, vector<string>, greater<string> > pq;
unordered_map<string, bool> chk;
stack<int> pos;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> s >> K;
	
	len = s.size();
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == ')' || s[i] == '(') len--;
	pq.push(s);
	
	while (K && !pq.empty())
	{
		h = pq.top();
		pq.pop();
		
		if (h.size() == len)
		{
			K--;
			continue;
		}
		for (int i = 0; i < h.size(); ++i)
		{
			if (h[i] == '(') pos.push(i);
			else if (h[i] == ')')
			{
				if (pos.size() == 1)
				{
					t = pos.top();
					
					a = b = "";
					if (t) a = b = h.substr(0, t);
					tmp = h.substr(t+1, i-t-1);
					a += tmp;
					reverse(tmp.begin(), tmp.end());
					for (int i = 0; i < tmp.size(); ++i)
					{
						if (tmp[i] == ')') tmp[i] = '(';
						else if (tmp[i] == '(') tmp[i] = ')';
					}
					b += tmp;
					if (i != h.size()-1)
					{
						a += h.substr(i+1);
						b += h.substr(i+1);
					}
					pos.pop();
					break;
				} 
				pos.pop();
			}
		}
		if (chk.find(a) == chk.end())
		{
			chk[a] = 1;
			pq.push(a);
		}
		if (a != b && chk.find(b) == chk.end())
		{
			chk[b] = 1;
			pq.push(b);
		}
	}
	if (!K) cout << h;
	else cout << "NO";
	return 0;
}