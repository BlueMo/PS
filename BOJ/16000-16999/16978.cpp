// 16978: 수열과 쿼리 22
// fail1~3: k번째까지 모든 1번 쿼리들을 update를 시키고 않고, k번째 1번 쿼리만 update 시킴

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;

struct Q1
{
	int idx, v;
}t1;
struct Q2
{
	int k, l, r, idx;
	
	bool operator < (Q2 a)const { return k < a.k; }
}t2;

int N, M, a, tree_size = 1;
ll tree[1<<18], ans[100001];
vector<Q1> q1;
vector<Q2> q2;

void updateST(int idx, int val)
{
	idx += tree_size;
	tree[idx] = val;
	
	while (idx > 1)
	{
		tree[idx>>1] = tree[idx] + tree[idx^1];
		idx >>= 1;
	}
}

ll getSum(int l, int r)
{
	ll sum = 0;
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1) sum += tree[l++];
		if (~r & 1) sum += tree[r--];
		l >>= 1, r >>= 1;
	}
	return sum;
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
		cin >> a;
		if (a == 1)
		{
			cin >> t1.idx >> t1.v;
			t1.idx--;
			q1.push_back(t1);
		}
		else
		{
			cin >> t2.k >> t2.l >> t2.r;
			t2.idx = q2.size();
			t2.k--,	t2.l--,	t2.r--;
			q2.push_back(t2);
		}
	}
	sort(q2.begin(), q2.end());
	
	int k = -1;
	for (Q2 i : q2)
	{
		if (i.k != k)
		{
			while (k < i.k)
			{
				k++;
				updateST(q1[k].idx, q1[k].v);
			}
		}
		ans[i.idx] = getSum(i.l, i.r);
	}
	
	for (int i = 0; i < q2.size(); ++i)
		cout << ans[i] << "\n";
	return 0;
}