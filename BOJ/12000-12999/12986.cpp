// 12986: 화려한 마을2
// fail1: mergeST 3,4번째 if문 위치 바뀜

#include<iostream>
#include<algorithm>
using namespace std;

int N, Q, l, r, tree_size=1;

struct ST
{
	int lmax, lval, rmax, rval, ans;
	
	ST(){}
	ST(int _v)
	{
		lmax = rmax = ans = 0;
		lval = rval = _v;
	}
}tree[1<<18];

ST mergeST(ST lnode, ST rnode)
{
	ST ret;
	ret.lmax = lnode.lmax;
	ret.lval = lnode.lval;
	ret.rmax = rnode.rmax;
	ret.rval = rnode.rval;
	ret.ans = max(lnode.ans, rnode.ans);
	
	if (lnode.lval == rnode.rval)
	{
		ret.lmax += ret.rmax;
		ret.rmax = ret.lmax;
		ret.ans = ret.rmax;
	}
	else if (lnode.lval == rnode.lval)
	{
		ret.lmax += rnode.lmax;
		ret.ans = max(ret.ans, ret.lmax);
	}
	else if (lnode.rval == rnode.rval)
	{
		ret.rmax += lnode.rmax;
		ret.ans = max(ret.ans, ret.rmax);
	}
	else if (lnode.rval == rnode.lval)
		ret.ans = max(ret.ans, lnode.rmax + rnode.lmax);
	
	return ret;
}

void buildST()
{
	for (int i = tree_size-1; i >= 1; --i)
		tree[i] = mergeST(tree[i<<1], tree[(i<<1)|1]);
}

int getCnt(int l, int r)
{
	ST sub_l(-100001), sub_r(100001);
	l += tree_size, r += tree_size;
	
	while (l <= r)
	{
		if (l & 1) sub_l = mergeST(sub_l, tree[l++]);
		if (~r & 1) sub_r = mergeST(tree[r--], sub_r);
		
		l >>= 1, r >>= 1;
	}
	sub_l = mergeST(sub_l, sub_r);
	return sub_l.ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N >> Q;
	while (tree_size < N) tree_size <<= 1;
	for (int i = tree_size; i < tree_size + N; ++i)
	{
		cin >> tree[i].lval;
		tree[i].rval = tree[i].lval;
		tree[i].rmax = tree[i].lmax = tree[i].ans = 1;
	}
	buildST();
	
	for (int i = 0; i < Q; ++i)
	{
		cin >> l >> r;
		cout << getCnt(l-1, r-1) << "\n";
	}
	return 0;
}