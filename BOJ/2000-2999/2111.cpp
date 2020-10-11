// 2111: 선인장
// fail1: 모든 정점이 연결되지 않은 경우 - 예외 처리 안해줌

#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int N, M, u, v, cnt, num, num2;
int idx[20002], low[20002], bcc[20002];
bool chk[20002];
vector<int> G[20002];

class BigInt{
public:
	string s;
	
	BigInt(): s(""){}
	BigInt(string str_val)
	{
		reverse(str_val.begin(), str_val.end());
		s = str_val;
	} 
	BigInt(int val)
	{
		while (val)
		{
			s.push_back(val%10 + '0');
			val /= 10;
		}
		if (s == "") s.push_back('0');
	}
	
	BigInt operator +(const BigInt &a) const
	{
		BigInt ret;
		int carry = 0;
		
		for (int i = 0; i < max(s.size(), a.s.size()); ++i)
		{
			carry += (i < s.size()? s[i]-'0' : 0) + (i < a.s.size()? a.s[i]-'0' : 0);
			
			ret.s.push_back(carry%10 + '0');
			carry /= 10;
		}
		if (carry) ret.s.push_back(carry + '0');
		
		return ret;
	}
	
	BigInt operator *(const BigInt &a) const
	{
		BigInt ret(0), tmp;
		
		for (int i = 0; i < a.s.size(); ++i)
		{
			tmp.s = string(i, '0') + s;
			for (int j = 1; j <= a.s[i]-'0'; ++j)
				ret = ret + tmp;
		}
		
		return ret;
	}
	
	friend ostream& operator<<(ostream& os, const BigInt &a)
	{
		for (int i = (int)a.s.size()-1; i >= 0; --i)
			os << a.s[i];
		
		return os;
	}
}ans("1");

void dfs(int u, int p)
{
	low[u] = idx[u] = ++num;
	for (int v : G[u])
	{
		if (v == p) continue;
		if (!idx[v])
		{
			dfs(v, u);
			low[u] = min(low[u], low[v]);
		}
		else low[u] = min(low[u], idx[v]);
		if (idx[u] > low[v])
		{
			if (chk[u]) ans.s[0] = '0';
			else chk[u] = 1;
		}
	}
}

void getBcc(int u, int c)
{
	if (c > 0) bcc[c]++;
	chk[u] = 1;
	for (int v : G[u])
	{
		if (chk[v]) continue;
		if (idx[u] <= low[v])
		{
			bcc[++num2]++;
			getBcc(v, num2);
		}
		else getBcc(v, c);
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> cnt >> u;
		for (int j = 1; j < cnt; ++j)
		{
			cin >> v;
			G[u].push_back(v);
			G[v].push_back(u);
			u = v;
		}
	}
	dfs(1, 0);
	for (int i = 1; i <= N; ++i)
	{
		if (!idx[i])
		{
			cout << "0";
			return 0;
		}
	}	
	memset(chk, 0, sizeof(chk));
	for (int i = 1; i <= N; ++i)
	{
		if (!chk[i]) getBcc(i, 0);
	}
	if (ans.s != "0")
	{
		for (int i = 0; i <= num2; ++i)
		{
			if (bcc[i] > 2)
				ans = ans * BigInt(bcc[i] + 1);
		}
	}
	cout << ans;
	return 0;
}