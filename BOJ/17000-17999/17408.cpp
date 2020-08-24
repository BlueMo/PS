// 17408: 수열과 쿼리 24
// fail: 1~2 Ai를 v로 바꿀 때 max 갱신하는 부분 실수
// 시간 없어서 대충 짜가지고 cmp 부분이 좀 비효율적임 -> 나중에 고쳐보자 -> 완료

#include<iostream>
#include<algorithm>
#define MAX(a,b) (((a)>(b))?(a):(b))
using namespace std;
typedef pair<int, int> ii;

int N, M, a, q, u, v, tree_size = 1;
ii tree[1<<18];

ii cmp(ii a, ii b)
{
	int x, y;
	x = MAX(a.second, b.second);
	if (a.first >= b.first)
	{
		y = MAX(b.first, x);
		a.second = y;
	}
	else
	{
		y = MAX(a.first, x);
		a.first = b.first;
		a.second = y;
	}
	return a;
}

void updateST(int idx, int val)
{
	idx += tree_size;
	tree[idx].first = val;
	
	while (idx > 1)
	{
		tree[idx>>1] = cmp(tree[idx], tree[idx^1]);
		idx >>= 1;
	}
}

int getAns(int l, int r)
{
	ii ans = {0, 0};
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1)
		{
			ans = cmp(ans, tree[l]);
			l++;
		}
		if (~r & 1)
		{
			ans = cmp(ans, tree[r]);
			r--;
		}
		l >>= 1, r >>= 1;
	}
	return ans.first + ans.second;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		updateST(i, a);
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q >> u >> v;
		if (q == 1) updateST(u-1, v);
		else cout << getAns(u-1, v-1) << "\n";
	}
	return 0;
}