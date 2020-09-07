// 1572: 중앙값

#include<iostream>
using namespace std;
typedef long long ll;

int N, K, a[250001], tree_size = 1<<17;
int tree[1<<18];
ll ans;

void updateST(int val, int is_push=1)
{
	val += tree_size;
	
	while (val >= 1)
	{
		tree[val] += is_push;
		val >>= 1;
	}
}

int get_middle()
{
	int k = (K+1)>>1;
	int idx = 1;
	
	while (idx < tree_size)
	{
		idx <<= 1;
		if (k > tree[idx]) k -= tree[idx++];
	}
	
	return idx - tree_size;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i)
		cin >> a[i];
	
	for (int i = 0; i < K; ++i)
		updateST(a[i]);
	ans += get_middle();
	for (int i = K; i < N; ++i)
	{
		updateST(a[i-K], -1);
		updateST(a[i]);
		ans += get_middle();
	}
	
	cout << ans;
	return 0;
}