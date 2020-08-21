// 13543: 수열과 쿼리 2

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;


int N, M, a, c[11][11];
ll p[200001][11], MOD = (ll)1<<32;

struct node
{
	node *l, *r, *p;		// left, right, parent
	int cnt;				// cnt(for find Kth)
	int v;
	ll eq[11];				// sum of Ai*(x+1)^k
	ll tmp[11];
	int lazy;				// lazy
	
	node(int _v)
	{
		l = r = p = NULL;
		v = _v;
		for (int i = 0; i < 11; ++i) eq[i] = _v;
		cnt = 1;
	}
};

struct SplayTree
{
	node *root;
	
	int size(){ return root->cnt; }
	
	void update(node *x)
	{
		int k;
		k = x->cnt = 1;
		if (x->l)
		{
			for (int i = 0; i < 11; ++i) x->tmp[i] = x->l->eq[i];
			x->cnt += x->l->cnt;
			k = x->cnt;
			for (int i = 0; i < 11; ++i)
			{
				for (int j = 0; j <= i; ++j) 
				{
					x->tmp[i] = (x->tmp[i] + x->v * c[i][j] * p[k-1][j]) % MOD;
				}
			}
		}
		else
		{
			for (int i = 0; i < 11; ++i) x->tmp[i] = x->v;
		}
		if (x->r)
		{
			for (int i = 0; i < 11; ++i)
			{
				for (int j = 0; j <= i; ++j)
					x->tmp[i] = (x->tmp[i] + x->r->eq[i-j] * c[i][j] * p[k][j]) % MOD;
			}
			x->cnt += x->r->cnt;
		}
		
		for (int i = 0; i < 11; ++i) x->eq[i] = x->tmp[i];
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
	
	node* interval(int l, int r)
	{
		/*node *x;
		
		if (r < N-1) x = findKth(r + 1);
		else x = findKth(r);
		
		if (l >= 1 && l != r)
		{
			node *y = findKth(l - 1);
			if (x != y)
			{
				y->r = x;
				x->p = y;
			}
		}
		return x->l;*/
		/*node *x = findKth(l - 1);
		root = x->r;
		root->p = NULL;
		x->r = findKth(r - l + 1);
		root->p = x;
		root = x;*/
	}
	
	void change(int k, int val)
	{
		
	}
	
	void preorder(int k, node *p)
	{
		if (!p) return;
		cout << "(" << p->v << ", " << p->eq[k] << ") ";
		cout << "L ";
		preorder(k, p->l);
		cout << "R ";
		preorder(k, p->r);
	}
	void print(int k, int type = 0)
	{
		if (!root)
		{
			cout << "NULL ";
			return;
		}
		if (type == 0) preorder(k, root);
		cout << endl;
	}
	
	int query(int l, int r, int k)
	{
		return interval(l, r)->eq[k];
	}
}A;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	c[0][0] = 1;
	for (int i = 1; i < 11; ++i)
	{
		c[i][0] = 1;
		for (int j = 1; j < i; ++j) c[i][j] = c[i-1][j-1] + c[i-1][j];
		c[i][i] = 1;
	}
	
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		p[i][0] = 1;
		for (int j = 1; j < 11; ++j) p[i][j] = (p[i][j-1] * i) % MOD;
	}
	for (int i = 0; i < N; ++i)
	{
		cin >> a;
		A.push(i, a);
	}
	cout << A.interval(0, 3) << endl;
/*	cin >> M;
	for (int i = N+1; i <= N+M; ++i)
	{
		p[i][0] = 1;
		for (int j = 1; j < 11; ++j) p[i][j] = p[i][j-1] * i;
	}
	for (int i = 0; i < M; ++i)
	{
		int u, v, k;
		cin >> u >> v >> k;
		cout << A.query(u, v, k) << endl;
	}*/
	return 0;
}