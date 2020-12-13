// 2261: 가장 가까운 두 점
// Divide & Conquer
// fail: merge sort 구현 오류

#include<bits/stdc++.h>
using namespace std;

struct P
{
	int x, y;
}p[100001], a[100001], b[100001], tmp[100001];
int N;

int min_dis(int l, int r)
{
	if (l == r)
	{
		a[l] = p[l];
		return 0x7fffffff;
	}
	
	int mid = (l+r)>>1;
	int d = min(min_dis(l, mid), min_dis(mid+1, r));
	
	if (!d) return 0;
	
	int i = l, j = mid+1, k = 0;
	while (1)
	{
		if (a[i].y <= a[j].y) b[k++] = a[i++];
		else b[k++] = a[j++];
		
		if (i > mid)
		{
			while (j <= r) b[k++] = a[j++];
			break;
		}
		else if (j > r)
		{
			while (i <= mid) b[k++] = a[i++];
			break;
		}
	}

	for (i = l; i <= r; ++i) a[i] = b[i-l];
	k = 0;
	for (i = l; i <= r; ++i)
	{
		int t1 = a[i].x - p[mid].x, t2 = p[mid+1].x - a[i].x;
		if (t1 >= 0 && t1*t1 < d) tmp[k++] = a[i];
		else if (t2 >= 0 && t2*t2 < d) tmp[k++] = a[i];
	}
	
	for (i = 0; i < k; ++i)
	{
		for (j = i+1; j < min(k, i+7); ++j)
			d = min(d, (tmp[i].x-tmp[j].x)*(tmp[i].x-tmp[j].x)+(tmp[i].y-tmp[j].y)*(tmp[i].y-tmp[j].y));
	}
	
	return d;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> p[i].x >> p[i].y;
	sort(p, p+N, [](const P &a, const P &b){ return a.x < b.x; });
	
	cout << min_dis(0, N-1);
	return 0;
}