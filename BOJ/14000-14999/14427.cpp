// 14427: 수열과 쿼리 15

#include<iostream>
#include<utility>
using namespace std;

int N, M, a, b, c, tree_size = 1;
pair<int, int> tree[1<<18];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	while (tree_size < N) tree_size <<= 1;
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		tree[tree_size + i] = {a, i+1};
	}
	for (int i = N; i < tree_size; ++i)
		tree[tree_size + i] = {0x7fffffff, i+1};
	
	for (int i = tree_size-1; i >= 1; --i)
	{
		if (tree[i<<1].first <= tree[(i<<1)|1].first)
			tree[i] = tree[i<<1];
		else
			tree[i] = tree[(i<<1)|1];
	}
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c;
			int idx = tree_size + b - 1;
			tree[idx].first = c;
			while (idx > 1)
			{
				idx >>= 1;
				if (tree[idx<<1].first <= tree[(idx<<1)|1].first)
					tree[idx] = tree[idx<<1];
				else
					tree[idx] = tree[(idx<<1)|1];
			}
		}
		else
			cout << tree[1].second << "\n";
	}
}