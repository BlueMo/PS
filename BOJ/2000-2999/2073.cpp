// 2073: 수도배관공사

#include<iostream>
#include<algorithm>
using namespace std;

int D, P, l[351], c[351];
int d[100002];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> D >> P;
	for (int i = 0; i < P; ++i)
		cin >> l[i] >> c[i];
	
	d[0] = 0x7fffffff;
	for (int i = 0; i < P; ++i)
	{
		for (int j = D-l[i]; j >= 0; --j)
			d[j+l[i]] = max(d[j+l[i]], min(d[j], c[i]));
	}
	
	cout << d[D];
	return 0;
}