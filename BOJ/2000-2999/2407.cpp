#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

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
}D[102][102];

int n, m;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    D[1][1] = string("1");
    D[1][2] = string("1");
    for (int i = 2; i <= n; i++){
        for (int j = 1; j <= i + 1; j++){
            D[i][j] = D[i-1][j-1] + D[i-1][j];
        }
    }
    cout << D[n][m + 1];
    return 0;
}