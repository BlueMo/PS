// 16903: 수열과 쿼리 20
// fail1: pop에서 cnt 감소를 리프노드에서만 실행함(for문 밖에 써버림)

#include<iostream>
using namespace std;

struct node
{
	node *l, *r;		// left: 0, right: 1
	int cnt;

	node()
	{
		l = r = NULL;
		cnt = 0;
	}
};

struct XOR_tree
{
	node *root;
	
	XOR_tree()
	{
		root = new node();
		node *x = root;
		for (int i = 30; i >= 0; --i)		// 0 하나 추가
		{
			if (!(x->l)) x->l = new node();
			x = x->l;
			x->cnt = x->cnt + 1;
		}
	}
	
	void push(int val)
	{
		node *x = root;
		for (int i = 30; i >= 0; --i)
		{
			if (val & (1<<i))
			{
				if (!(x->r)) x->r = new node();
				x = x->r;
			}
			else
			{
				if (!(x->l)) x->l = new node();
				x = x->l;
			}
			x->cnt = x->cnt + 1;
		}
	}
	
	void pop(int val)
	{
		node *x = root;
		for (int i = 30; i >= 0; --i)
		{
			if (val & (1<<i)) x = x->r;
			else x = x->l;
			x->cnt = x->cnt - 1;
		}
	}
	
	int query(int val)
	{
		node *x = root;
		int ans = 0;
		for (int i = 30; i >= 0; --i)
		{
			if (val & (1<<i))
			{
				if (x->l && x->l->cnt)
				{
					x = x->l;
					ans |= 1<<i;
				}
				else x = x->r;
			}
			else
			{
				if (x->r && x->r->cnt)
				{
					x = x->r;
					ans |= 1<<i;
				}
				else x = x->l;
			}
		}
		return ans;
	}
}tree;
int M, q, x;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> M;
	for (int i = 0; i < M; ++i)
	{
		cin >> q >> x; 
		if (q == 1) tree.push(x);
		else if (q == 2) tree.pop(x);
		else cout << tree.query(x) << "\n";
	}
	return 0;
}