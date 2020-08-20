// 13543: 수열과 쿼리 2

#include<iostream>
#include<algorithm>
#define MOD 1<<32
using namespace std;
typedef long long ll;

struct node
{
	node *l, *r, *p;		// left, right, parent
	int v, cnt;				// value, cnt(for find Kth)
	
	node(int _v)
	{
		l = r = p = NULL;
		v = _v;
		cnt = 1;
	}
};

struct SpalyTree
{
	node *root;
	
	int size(){ return root->cnt; }
	void update(node *x)
	{
		x->cnt = 1;
		if (x->l)
		{
			x->cnt += x->l->cnt;
		}
		if (x->r)
		{
			x->cnt += x->r->cnt;
		}
	}
	
	void rotate(node *x)
	{
		node *p = x->p;
		node *g = p->p;
		node *b = NULL;
		if (x == p->l)
		{
			p->l = b = x->r;
			x->r = p;
		}
		else
		{
			p->r = b = x->l;
			x->l = p;
		}
		x->p = g;
		p->p = x;
		if (b) b->p = p;
		if (!g) root = x;
		else if (g->l == p) g->l = x;
		else g->r = x;
		update(p);
		update(x);
	}
	
	void splay(node *x)
	{
		while (x->p)
		{
			node *p = x->p;
			node *g = p->p;
			if (p != root)
			{
				if ( (g->l == p) == (p->l == x) ) rotate(p);
				else rotate(x);
			}
			rotate(x);
		}
	}
	
	node* findKth(int k)		// 0-based
	{
		node *x = root;
		
		while (1)
		{
			while (x->l && x->l->cnt > k) x = x->l;
			if (x->l) k -= x->l->cnt;
			if (!k) break;
			k--;
			x = x->r;
		}
		splay(x);
		return x;
	}
	
	void push(int k, int val)
	{
		node *n = new node(val);
		if (!root)
		{
			root = n;
			return;
		}
		
		if (k != size())
		{
			findKth(k);
			if (root->l)
			{
				root->l->p = n;
				n->l = root->l;
			}
			root->l = n;
			n->p = root;
			
			node *x = n;
		}
		else
		{
			findKth(k-1)->r = n;
			n->p = root;
		}
		splay(n);
	}
	
	void pop(int k)
	{
		node *d = findKth(k);
		if (d->l)
		{
			root = d->l;
			root->p = NULL;	
			if (d->r)
			{
				node *x = root;
				while (x->r) x = x->r;
				x->r = d->r;
				d->r->p = x;
				splay(x);
			}
			delete d;
			return;
		}
		if (size() == 1)
		{
			delete d;
			root = NULL;
			return;
		}
		root = d->r;
		d->r->p = NULL;
		delete d;
	}
	
	void interval(int l, int r)
	{
		node *x = findKth(l - 1);
		root = x->r;
		root->p = NULL;
		x->r = findKth(r - l + 1);
		root->p = x;
		root = x;
	}
	
	void preorder(node *p)
	{
		if (!p) return;
		cout << p->v << " ";
		cout << "L ";
		preorder(p->l);
		cout << "R ";
		preorder(p->r);
	}
	void print(int type = 0)
	{
		if (!root)
		{
			cout << "NULL ";
			return;
		}
		if (type == 0) preorder(root);
		cout << endl;
	}
}A;

int N, a;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		A.push(i, a);
	}
	A.push(4, 20);
	A.interval(1, 3);
	A.print();
	return 0;
}